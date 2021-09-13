// -*- mode: c++; indent-tabs-mode: t; tab-width: 4; c-basic-offset: 4; -*-
#include <iostream>
#include "ThermoLimiter2Service_impl.h"

ThermoLimiter2Service_impl::ThermoLimiter2Service_impl()
{
}

ThermoLimiter2Service_impl::~ThermoLimiter2Service_impl()
{
}

CORBA::Boolean ThermoLimiter2Service_impl::setParameter(const OpenHRP::ThermoLimiter2Service::tlParam& i_param)
{
    //return m_thermolimiter->setParameter(i_param);
	return true;
};

CORBA::Boolean ThermoLimiter2Service_impl::getParameter(OpenHRP::ThermoLimiter2Service::tlParam_out i_param)
{
    //i_param = OpenHRP::ThermoLimiter2Service::tlParam();
    //return m_thermolimiter->getParameter(i_param);
	return true;
};

// void ThermoLimiter2Service_impl::thermolimiter(ThermoLimiter2 *i_thermolimiter)
// {
//     m_thermolimiter = i_thermolimiter;
// }
