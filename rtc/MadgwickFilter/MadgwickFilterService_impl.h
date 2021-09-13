// -*-C++-*-
#ifndef MadgwickFilterSERVICESVC_IMPL_H
#define MadgwickFilterSERVICESVC_IMPL_H

#include "madgwick_filter_rtc/idl/MadgwickFilterService.hh"

class MadgwickFilter;
using namespace MadgwickFilterRtcIdl;

class MadgwickFilterService_impl
  : public virtual POA_MadgwickFilterRtcIdl::MadgwickFilterService,
    public virtual PortableServer::RefCountServantBase
{
public:
  MadgwickFilterService_impl();// 実装は.cppファイルの方に書かないと、registerProvider時にSegmentation Faultになる
  virtual ~MadgwickFilterService_impl();
  CORBA::Boolean setParams(const MadgwickFilterRtcIdl::MadgwickFilterService::MadgwickFilterParam& i_param);
  CORBA::Boolean getParams(MadgwickFilterRtcIdl::MadgwickFilterService::MadgwickFilterParam_out i_param);
  //
  void setComp(MadgwickFilter *i_comp);
private:
  MadgwickFilter *comp_;
};

#endif
