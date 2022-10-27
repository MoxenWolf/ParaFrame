#pragma once

#include <string>


namespace ParaPlugin {
    // typedef bruteforce (prior to new templated using statements)
    typedef void (*ft_void)();
    typedef void (*ft_void_bool)(bool);
    typedef void (*ft_void_int_bool)(int, bool);
    typedef void (*ft_void_int)(int, float);
    typedef void (*ft_void_float_float)(float, float);
    typedef void (*ft_void_int_float)(int, float);

    // more elegant using templates 
    template<typename T>
    using ft_single = void (*)(T);

    template<typename T, typename K>
    using ft_dual = void (*)(T, K);

    // most elegant using template! (see ICalibratableArray)
    template<typename ...Args>
    using ft_multi = void (*)(Args...);

    // interface defs
    struct IParaBase {
        IParaBase() = default;
        virtual ~IParaBase() = default;

        virtual void pluginSetup() = 0;
        ft_void_bool pluginSetupComplete = nullptr;
        void setCb_pluginSetupComplete(ft_void_bool cb) {
            pluginSetupComplete = cb;
        }

        virtual void pluginTakedown() = 0;
        ft_multi<bool> pluginTakedownComplete = nullptr; //using new template approach
        void setCb_pluginTakedownComplete(ft_multi<bool> cb) {
            pluginTakedownComplete = cb;
        }
    };

    struct IHapticInput {
        IHapticInput() = default;
        virtual ~IHapticInput() = default;

        virtual void vibrateForMs(int intensity, int ms) = 0;
        virtual void stopAllFeedback() = 0;
    };

    struct IButtonArray {
        IButtonArray() = default;
        virtual ~IButtonArray() = default;

        ft_void_int_bool buttonStateChanged = nullptr;
        void setCb_buttonStateChanged(ft_void_int_bool cb) {
            buttonStateChanged = cb;
        }
    };

    struct IJoystickArray {
        IJoystickArray() = default;
        virtual ~IJoystickArray() = default;

        ft_void_float_float joystickStateChanged = nullptr;
        void setCb_joystickStateChanged(ft_void_float_float cb) {
            joystickStateChanged = cb;
        }
    };

    struct IAnalogAxisArray {
        IAnalogAxisArray() = default;
        virtual ~IAnalogAxisArray() = default;

        ft_void_int_float analogButtonStateChanged = nullptr;
        void setCb_analogButtonStateChanged(ft_void_int_float) {
            analogButtonStateChanged = nullptr;
        }
    };

    struct ILightBox {
        ILightBox() = default;
        virtual ~ILightBox() = default;

        virtual void activateLight(std::string color, int time) = 0;
        virtual void deactivateLight() = 0;
    };

    struct ICalibratableArray {
        ICalibratableArray() = default;
        virtual ~ICalibratableArray() = default;

        virtual void calibrate(int device, int value) = 0;
        ft_multi<int, int> calibrateCompleted = nullptr; //uses new "using template multi"
        void setCb_calibrateCompleted(ft_multi<int, int> cb) {
            calibrateCompleted = cb;
        }

    };
}

