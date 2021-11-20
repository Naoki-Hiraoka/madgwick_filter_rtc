// -*-C++-*-
#ifndef MadgwickFilterSERVICESVC_IMPL_H
#define MadgwickFilterSERVICESVC_IMPL_H

#include "madgwick_filter_rtc/idl/MadgwickFilterService.hh"

class MadgwickFilter;
using namespace madgwick_filter_rtc;

class MadgwickFilterService_impl
  : public virtual POA_madgwick_filter_rtc::MadgwickFilterService,
    public virtual PortableServer::RefCountServantBase
{
public:
  MadgwickFilterService_impl();// 実装は.cppファイルの方に書かないと、registerProvider時にSegmentation Faultになる
  virtual ~MadgwickFilterService_impl();
  CORBA::Boolean setParams(const madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam& i_param);
  CORBA::Boolean getParams(madgwick_filter_rtc::MadgwickFilterService::MadgwickFilterParam_out i_param);
  //
  void setComp(MadgwickFilter *i_comp);
private:
  MadgwickFilter *comp_;
};

#endif
