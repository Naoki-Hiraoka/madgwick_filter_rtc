// -*- mode: c++; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*-
#ifndef THERMOLIMITERSERVICESVC_IMPL_H
#define THERMOLIMITERSERVICESVC_IMPL_H

#include "madgwick_filter_rtc/idl/ThermoLimiter2Service.hh"

using namespace OpenHRP;

class ThermoLimiter2Service_impl
	: public virtual POA_OpenHRP::ThermoLimiter2Service,
	  public virtual PortableServer::RefCountServantBase
{
public:
	/**
	   \brief constructor
	*/
	ThermoLimiter2Service_impl();

	/**
	   \brief destructor
	*/
	virtual ~ThermoLimiter2Service_impl();
	CORBA::Boolean setParameter(const OpenHRP::ThermoLimiter2Service::tlParam& i_param);
	CORBA::Boolean getParameter(OpenHRP::ThermoLimiter2Service::tlParam_out i_param);
	//void thermolimiter(ThermoLimiter2 *i_thermolimiter);
private:
	//	ThermoLimiter2 *m_thermolimiter;
};

#endif
