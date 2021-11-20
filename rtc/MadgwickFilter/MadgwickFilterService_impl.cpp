#include "MadgwickFilterService_impl.h"
#include "MadgwickFilter.h"

MadgwickFilterService_impl::MadgwickFilterService_impl()
{
}

MadgwickFilterService_impl::~MadgwickFilterService_impl()
{
}

void MadgwickFilterService_impl::setComp(MadgwickFilter *i_comp)
{
  comp_ = i_comp;
}

void MadgwickFilterService_impl::setParams(const madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param)
{
  comp_->setParams(i_param);
  return;
};

void MadgwickFilterService_impl::getParams(madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam_out i_param)
{
  i_param = madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam(); // 配列がない場合はこの形．ある場合はポインタになるらしい
  comp_->getParams(i_param);
  return;
};

