#include "MadgwickFilter.h"
#include <Eigen/Eigen>

#define DEBUGP (loop%200==0)
#define DEBUGP_ONCE (loop==0)

static const char* MadgwickFilter_spec[] = {
  "implementation_id", "MadgwickFilter",
  "type_name",         "MadgwickFilter",
  "description",       "MadgwickFilter component",
  "version",           "0.0",
  "vendor",            "Naoki-Hiraoka",
  "category",          "example",
  "activity_type",     "DataFlowComponent",
  "max_instance",      "10",
  "language",          "C++",
  "lang_type",         "compile",
  "conf.default.debugLevel", "0",
  ""
};

MadgwickFilter::MadgwickFilter(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    ports_(),
    m_debugLevel_(0)
{
  this->ports_.m_service0_.setComp(this);
}

RTC::ReturnCode_t MadgwickFilter::onInitialize(){
  bindParameter("debugLevel", this->m_debugLevel_, "0");

  addInPort("rate", this->ports_.m_rateIn_);
  addInPort("acc", this->ports_.m_accIn_);
  addOutPort("rpy", this->ports_.m_rpyOut_);
  this->ports_.m_MadgwickFilterServicePort_.registerProvider("service0", "MadgwickFilterService", this->ports_.m_service0_);
  addPort(this->ports_.m_MadgwickFilterServicePort_);
  this->loop_ = 0;

  double gain = 0.1;
  if(this->getProperties().hasKey("gain")) gain = std::stod(std::string(this->getProperties()["gain"]));
  else if(this->m_pManager->getConfig().hasKey("gain")) gain = std::stod(std::string(this->m_pManager->getConfig()["gain"])); // 引数 -o で与えたプロパティを捕捉
  std::cerr << "[" << this->m_profile.instance_name << "] gain: " << gain <<std::endl;

  double zeta = 0.0;
  if(this->getProperties().hasKey("zeta")) zeta = std::stod(std::string(this->getProperties()["zeta"]));
  else if(this->m_pManager->getConfig().hasKey("zeta")) zeta = std::stod(std::string(this->m_pManager->getConfig()["zeta"])); // 引数 -o で与えたプロパティを捕捉
  std::cerr << "[" << this->m_profile.instance_name << "] zeta: " << zeta <<std::endl;

  this->madgwickFilterParam_.gain = gain;
  this->madgwickFilterParam_.zeta = zeta;
  this->imuFilter_.setAlgorithmGain(this->madgwickFilterParam_.gain);
  this->imuFilter_.setDriftBiasGain(this->madgwickFilterParam_.zeta);

  this->ports_.m_acc_.data.ax = 0.0;
  this->ports_.m_acc_.data.ay = 0.0;
  this->ports_.m_acc_.data.az = 9.8;
  this->ports_.m_rate_.data.avx = 0.0;
  this->ports_.m_rate_.data.avy = 0.0;
  this->ports_.m_rate_.data.avz = 0.0;

  return RTC::RTC_OK;
}

RTC::ReturnCode_t MadgwickFilter::onExecute(RTC::UniqueId ec_id){

  std::string instance_name = std::string(this->m_profile.instance_name);

  if(this->ports_.m_rateIn_.isNew() || this->ports_.m_accIn_.isNew()) {
    this->ports_.m_rateIn_.read();
    this->ports_.m_accIn_.read();
  }

  double dt = 1.0 / this->get_context(ec_id)->get_rate();

  // update imu
  this->imuFilter_.madgwickAHRSupdateIMU(this->ports_.m_rate_.data.avx,
                                         this->ports_.m_rate_.data.avy,
                                         this->ports_.m_rate_.data.avz,
                                         this->ports_.m_acc_.data.ax,
                                         this->ports_.m_acc_.data.ay,
                                         this->ports_.m_acc_.data.az,
                                         dt);
  Eigen::Quaterniond q;
  this->imuFilter_.getOrientation(q.w(),q.x(),q.y(),q.z());

  // write outport
  Eigen::Vector3d rpy = q.toRotationMatrix().eulerAngles(2,1,0);
  this->ports_.m_rpy_.data.r = rpy[2];
  this->ports_.m_rpy_.data.p = rpy[1];
  this->ports_.m_rpy_.data.y = rpy[0];
  this->ports_.m_rpy_.tm = this->ports_.m_acc_.tm;
  this->ports_.m_rpyOut_.write();

  this->loop_++;
  return RTC::RTC_OK;
}

CORBA::Boolean MadgwickFilter::setParams(const madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param){
  std::cerr << "[" << m_profile.instance_name << "] "<< "setParams" << std::endl;
  this->madgwickFilterParam_ = i_param;
  this->imuFilter_.setAlgorithmGain(this->madgwickFilterParam_.gain);
  this->imuFilter_.setDriftBiasGain(this->madgwickFilterParam_.zeta);

  return true;
}


CORBA::Boolean MadgwickFilter::getParams(madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param){
  std::cerr << "[" << m_profile.instance_name << "] "<< "getParams" << std::endl;
  i_param = this->madgwickFilterParam_;
  return true;
}

RTC::ReturnCode_t MadgwickFilter::onActivated(RTC::UniqueId ec_id){
  std::cerr << "[" << m_profile.instance_name << "] "<< "onActivated(" << ec_id << ")" << std::endl;
  return RTC::RTC_OK;
}
RTC::ReturnCode_t MadgwickFilter::onDeactivated(RTC::UniqueId ec_id){
  std::cerr << "[" << m_profile.instance_name << "] "<< "onDeactivated(" << ec_id << ")" << std::endl;
  return RTC::RTC_OK;
}
RTC::ReturnCode_t MadgwickFilter::onFinalize(){ return RTC::RTC_OK; }

extern "C"{
    void MadgwickFilterInit(RTC::Manager* manager) {
        RTC::Properties profile(MadgwickFilter_spec);
        manager->registerFactory(profile, RTC::Create<MadgwickFilter>, RTC::Delete<MadgwickFilter>);
    }
};
