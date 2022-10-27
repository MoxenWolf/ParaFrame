#include "dan_tmp.h"

class XBoxController : virtual public ParaPlugin::IParaBase,
	virtual public ParaPlugin::IHapticInput,
	virtual public ParaPlugin::IButtonArray,
	virtual public ParaPlugin::IJoystickArray,
	virtual public ParaPlugin::IAnalogAxisArray,
	virtual public ParaPlugin::ILightBox,
	virtual public ParaPlugin::ICalibratableArray {
public:
	XBoxController() {
		//init code
	}

	~XBoxController() {
		//destruct code
	}

	void pluginSetup() {

		/* 
		* example of using a signal call outside of plugin
		* this will be changed to encap in a SIGNALS or somethig similar
		* so the final call will prob be some intellisense access'ble like...
		* this->SIGNALS.pluginSetupComplete(true);
		*/
		if (pluginSetupComplete) {
			this->pluginSetupComplete(true);
		}
	}

	void pluginTakedown() {

	}

	void vibrateForMs(int intensity, int ms) {

	}
	
	void stopAllFeedback() {

	}

	void activateLight(std::string color, int time) {

	}

	void deactivateLight() {

	}

	void calibrate(int device, int value) {

	}
};