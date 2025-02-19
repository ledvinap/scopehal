/***********************************************************************************************************************
*                                                                                                                      *
* libscopehal v0.1                                                                                                     *
*                                                                                                                      *
* Copyright (c) 2012-2023 Andrew D. Zonenberg and contributors                                                         *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

#ifndef SiglentPowerSupply_h
#define SiglentPowerSupply_h

/**
	@brief A Siglent SPD3303x power supply
 */
class SiglentPowerSupply
	: public virtual SCPIPowerSupply
	, public virtual SCPIDevice
{
public:
	SiglentPowerSupply(SCPITransport* transport);
	virtual ~SiglentPowerSupply();

	//Device information
	virtual std::string GetName() override;
	virtual std::string GetVendor() override;
	virtual std::string GetSerial() override;
	virtual uint32_t GetInstrumentTypesForChannel(size_t i) override;

	//Device capabilities
	virtual bool SupportsIndividualOutputSwitching() override;
	virtual bool SupportsVoltageCurrentControl(int chan);

	//Read sensors
	virtual double GetPowerVoltageActual(int chan) override;	//actual voltage after current limiting
	virtual double GetPowerVoltageNominal(int chan) override;	//set point
	virtual double GetPowerCurrentActual(int chan) override;	//actual current drawn by the load
	virtual double GetPowerCurrentNominal(int chan) override;	//current limit
	virtual bool GetPowerChannelActive(int chan) override;

	//Configuration
	virtual void SetPowerVoltage(int chan, double volts) override;
	virtual void SetPowerCurrent(int chan, double amps) override;
	virtual void SetPowerChannelActive(int chan, bool on) override;
	virtual bool IsPowerConstantCurrent(int chan) override;

protected:
	unsigned int GetStatusRegister();

	bool m_ch3on;

public:
	static std::string GetDriverNameInternal();
	POWER_INITPROC(SiglentPowerSupply);
};

#endif
