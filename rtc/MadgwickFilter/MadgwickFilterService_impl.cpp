#include "MadgwickFilterService_impl.h"
#include "MadgwickFilter.h"

void MadgwickFilterService_impl::setComp(MadgwickFilter *i_comp)
{
  comp_ = i_comp;
}

CORBA::Boolean MadgwickFilterService_impl::setParams(const MadgwickFilterRtcIdl::MadgwickFilterService::MadgwickFilterParam& i_param)
{
  return comp_->setParams(i_param);
};

CORBA::Boolean MadgwickFilterService_impl::getParams(MadgwickFilterRtcIdl::MadgwickFilterService::MadgwickFilterParam_out i_param)
{
  i_param = MadgwickFilterRtcIdl::MadgwickFilterService::MadgwickFilterParam(); // 配列がない場合はこの形．ある場合はポインタになるらしい
  return comp_->getParams(i_param);
};

