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

#ifndef SCPIBERT_h
#define SCPIBERT_h

/**
	@brief An SCPI-based BERT
 */
class SCPIBERT 	: public virtual BERT
				, public virtual SCPIInstrument
{
public:
	SCPIBERT();
	virtual ~SCPIBERT();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Dynamic creation
public:
	typedef SCPIBERT* (*BERTCreateProcType)(SCPITransport*);
	static void DoAddDriverClass(std::string name, BERTCreateProcType proc);

	static void EnumDrivers(std::vector<std::string>& names);
	static SCPIBERT* CreateBERT(std::string driver, SCPITransport* transport);

	virtual std::string GetDriverName() =0;

protected:
	//Class enumeration
	typedef std::map< std::string, BERTCreateProcType > BERTCreateMapType;
	static BERTCreateMapType m_powercreateprocs;
};

#define BERT_INITPROC(T) \
	static SCPIBERT* CreateInstance(SCPITransport* transport) \
	{	return new T(transport); } \
	virtual std::string GetDriverName() \
	{ return GetDriverNameInternal(); }

#define AddBERTDriverClass(T) SCPIBERT::DoAddDriverClass(T::GetDriverNameInternal(), T::CreateInstance)


#endif
