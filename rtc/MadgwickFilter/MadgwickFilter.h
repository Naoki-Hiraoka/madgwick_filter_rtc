#ifndef MadgwickFilterRTC_H
#define MadgwickFilterRTC_H

#include <memory>

#include <rtm/idl/BasicDataType.hh>
#include <rtm/idl/ExtendedDataTypes.hh>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/CorbaNaming.h>

#include <imu_filter_madgwick/imu_filter.h>

#include "MadgwickFilterService_impl.h"

class MadgwickFilter : public RTC::DataFlowComponentBase{
public:
  class Ports {
  public:
    Ports() :
      m_rateIn_("rate", m_rate_),
      m_accIn_("acc", m_acc_),
      m_rpyOut_("rpy", m_rpy_),

      m_MadgwickFilterServicePort_("MadgwickFilterService") {
    }

    RTC::TimedAngularVelocity3D m_rate_;
    RTC::InPort<RTC::TimedAngularVelocity3D> m_rateIn_;
    RTC::TimedAcceleration3D m_acc_;
    RTC::InPort<RTC::TimedAcceleration3D> m_accIn_;
    RTC::TimedOrientation3D m_rpy_;
    RTC::OutPort<RTC::TimedOrientation3D> m_rpyOut_;

    MadgwickFilterService_impl m_service0_;
    RTC::CorbaPort m_MadgwickFilterServicePort_;
  };

public:
  MadgwickFilter(RTC::Manager* manager);
  virtual RTC::ReturnCode_t onInitialize();
  virtual RTC::ReturnCode_t onFinalize();
  virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
  virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
  CORBA::Boolean setParams(const madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param);
  CORBA::Boolean getParams(madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param);

protected:

  unsigned int m_debugLevel_;
  unsigned int loop_;

  Ports ports_;

  madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam madgwickFilterParam_;
  ImuFilter imuFilter_;
};


extern "C"
{
  void MadgwickFilterInit(RTC::Manager* manager);
};

#endif // MadgwickFilterRTC_H
