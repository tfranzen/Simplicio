#include "stdafx.h"
//#using <DataStructures.dll>
#include "SimplicioServer.h"
#include "Form1.h"
namespace forms2{
	//using namespace DataStructures;
	//using namespace System::Collections::Generic;
	using namespace System::Runtime::Remoting;
	using namespace System::Runtime::Remoting::Channels;
	using namespace System::Runtime::Remoting::Channels::Tcp;
	SimplicioServer::SimplicioServer(Form1^ f){
		mainForm=f;
		serverName = gcnew String("camera top");
		setNextTimeMainForm = gcnew DelegateTime(f,&Form1::setNextTime);
		seqStartedMainForm = gcnew DelegateVars(f,&Form1::sequenceStarted);
		seqEndedMainForm = gcnew DelegateE(f,&Form1::sequenceEnded);
		connect();	
	}
	void SimplicioServer::connect(){
		//RemotingConfiguration::Configure("forms2.exe.config",false);
		try{
			TcpChannel^ tcpChannel  = gcnew TcpChannel(5678);
			ChannelServices::RegisterChannel(tcpChannel, false);
			ObjRef^ objRef  = RemotingServices::Marshal(this, "serverCommunicator"); 
		}catch(Exception^){}
	}
	bool SimplicioServer::armTasks(UInt32 clockID)
	{	
		return true;
	}
	ServerCommunicator::BufferGenerationStatus SimplicioServer::generateBuffers(int listIterationNumber)
    {
		return 	ServerCommunicator::BufferGenerationStatus::Success;
    }

    bool SimplicioServer::generateTrigger()
    {
        return true;
    }
	List<HardwareChannel>^ SimplicioServer::getHardwareChannels()
    {
        return gcnew List<HardwareChannel>();
    }
	void SimplicioServer::setServerName(String^ name){
		serverName  = name;
	}
	String^ SimplicioServer::getServerName()
    {
        return serverName;
    }

	ServerSettingsInterface^ SimplicioServer::getServerSettings()
    {
        return gcnew ServerSettingsInterface();
    }

	void SimplicioServer::nextRunTimeStamp(DateTime timeStamp)
    {
		array<Object^>^ parameters = gcnew array<Object^>(1);
		parameters[0] = timeStamp;
		mainForm->BeginInvoke(setNextTimeMainForm, parameters);

    }

	bool SimplicioServer::outputGPIBGroup(GPIBGroup^ gpibGroup, SettingsData^ settings)
    {
        return true;
    }

	bool SimplicioServer::outputRS232Group(RS232Group^ rs232Group, SettingsData^ settings)
    {
        return true;
    }

    bool SimplicioServer::outputSingleTimestep(SettingsData^ settings, SingleOutputFrame^ output)
    {
        return true;
    }

    bool SimplicioServer::ping()
    {
        //messageLog(this, new MessageEvent("Received PING from client."));
        return true;
    }

    bool SimplicioServer::runSuccess()
    {
       mainForm->BeginInvoke(seqEndedMainForm,gcnew array<Object^>(0));
		return true;
    }

    bool SimplicioServer::setSequence(SequenceData^ sequence)
    {
		List<Variable^>^ vars = sequence->Variables;
		LinkedList<Variable^>^ listVars = gcnew LinkedList<Variable^>();
		int count(0);
		for each(Variable^ var in vars){
			if (var->ListDriven){
				Variable^ newVar = gcnew Variable();
				newVar->VariableValue = var->VariableValue;
				newVar->VariableName = var->VariableName;
				listVars->AddLast(newVar);
				count++;
			}
		}

        

		int triggerCount = 0;
		double exptime = 0;
		if(triggerChannel >-1){ //found a trigger Channel
			for each(TimeStep^ ts in sequence->TimeSteps){ //now count timesteps where it is active
				if(ts->StepEnabled){
					if(ts->DigitalData[triggerChannel]->getValue())
					{
						triggerCount++;
						if(exptime == 0)	exptime = ts->StepDuration->getBaseValue();
					}
					else if (ts->DigitalData[triggerChannel]->usesPulse())
					{
						if(exptime == 0)	exptime = ts->DigitalData[triggerChannel]->DigitalPulse->pulseDuration->getBaseValue();
						triggerCount++;
					}
				}
			}

		}

		array<Object^>^ parameters = gcnew array<Object^>(4);
		parameters[0] = listVars;
		parameters[1] = sequence->ListIterationNumber;
		parameters[2] = triggerCount;
		parameters[3] = exptime;
		mainForm->BeginInvoke(seqStartedMainForm, parameters);
		mySequence = sequence;
        return true;
    }

    bool SimplicioServer::setSettings(SettingsData^ settings)
    {
		mySettings = settings;
		Dictionary<int,LogicalChannel^>^ dc = settings->logicalChannelManager->Digitals;
		triggerChannel = -1;
		for each (int i in dc->Keys){
			if(dc[i]->Name == serverName){
				// found trigger Channel
				triggerChannel = i;

			}
		}
        return true;
    }

    void SimplicioServer::stop()
    {
        
    }
}