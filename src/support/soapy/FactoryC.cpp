// Copyright (c) 2014-2018 Josh Blum
// SPDX-License-Identifier: BSL-1.0

#include "ErrorHelpers.hpp"
#include "TypeHelpers.hpp"
#include "Device.h"
#include "Device.hpp"
#include <cstdlib>
#include <cstring>

extern "C" {

SoapySDRKwargs *SoapySDRDevice_enumerate(const SoapySDRKwargs *args, size_t *length)
{
    *length = 0;
    __SOAPY_SDR_C_TRY
    return toKwargsList(SoapySDR::Device::enumerate(toKwargs(args)), length);
    __SOAPY_SDR_C_CATCH_RET(nullptr);
}

SoapySDRKwargs *SoapySDRDevice_enumerateStrArgs(const char *args, size_t *length)
{
    *length = 0;
    __SOAPY_SDR_C_TRY
    return toKwargsList(SoapySDR::Device::enumerate(args), length);
    __SOAPY_SDR_C_CATCH_RET(nullptr);
}

SoapySDRDevice *SoapySDRDevice_make(const SoapySDRKwargs *args)
{
    __SOAPY_SDR_C_TRY
    return (SoapySDRDevice *)SoapySDR::Device::make(toKwargs(args));
    __SOAPY_SDR_C_CATCH_RET(nullptr);
}

SoapySDRDevice *SoapySDRDevice_makeStrArgs(const char *args)
{
    __SOAPY_SDR_C_TRY
    return (SoapySDRDevice *)SoapySDR::Device::make((args==nullptr)?"":args);
    __SOAPY_SDR_C_CATCH_RET(nullptr);
}

int SoapySDRDevice_unmake(SoapySDRDevice *device)
{
    __SOAPY_SDR_C_TRY
    SoapySDR::Device::unmake((SoapySDR::Device *)device);
    __SOAPY_SDR_C_CATCH
}

/*******************************************************************
 * Parallel support
 ******************************************************************/
SoapySDRDevice **SoapySDRDevice_make_each(SoapySDRKwargs *argsList, const size_t length)
{
    __SOAPY_SDR_C_TRY
    const auto devices = SoapySDR::Device::make(toKwargsList(argsList, length));
    auto outDevices = (SoapySDRDevice **)calloc(length, sizeof(SoapySDRDevice *));
    for (size_t i = 0; i < length; i++) outDevices[i] = (SoapySDRDevice *)devices[i];
    return outDevices;
    __SOAPY_SDR_C_CATCH_RET(nullptr);
}

int SoapySDRDevice_unmake_each(SoapySDRDevice **devices, const size_t length)
{
    __SOAPY_SDR_C_TRY
    std::vector<SoapySDR::Device *> devicesVector(length);
    for (size_t i = 0; i < length; i++) devicesVector[i] = (SoapySDR::Device *)devices[i];
    free(devices);
    SoapySDR::Device::unmake(devicesVector);
    __SOAPY_SDR_C_CATCH
}

}
