module VulkanSimplifiers.EventHandling;

EventHandlingSimplifier::EventHandlingSimplifier(EventHandlingInternal& ref) : _internal(ref)
{
}

EventHandlingSimplifier::~EventHandlingSimplifier()
{
}

void EventHandlingSimplifier::HandleEvents() const
{
	_internal.HandleEvents();
}

IDObject<std::pair<QuitEventFunction, void*>> EventHandlingSimplifier::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
{
	return _internal.RegisterQuitEventCallback(function, data, add);
}

IDObject<std::pair<AppTerminatingEventFunction, void*>> EventHandlingSimplifier::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppTerminatingEventCallback(function, data, add);
}

IDObject<std::pair<AppLowMemoryEventFunction, void*>> EventHandlingSimplifier::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppLowMemoryWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterBackgroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterBackgroundEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterForegroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterForegroundEventCallback(function, data, add);
}

IDObject<std::pair<LocaleChangedEventFunction, void*>> EventHandlingSimplifier::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterLocaleChangingEventCallback(function, data, add);
}

IDObject<std::pair<DisplayEventFunction, void*>> EventHandlingSimplifier::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDisplayEventCallback(function, data, add);
}

IDObject<std::pair<WindowEventFunction, void*>> EventHandlingSimplifier::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
{
	return _internal.RegisterWindowEventCallback(function, data, add);
}

IDObject<std::pair<KeyboardEventFunction, void*>> EventHandlingSimplifier::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeyboardEventCallback(function, data, add);
}

IDObject<std::pair<KeymapChangeEventFunction, void*>> EventHandlingSimplifier::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeymapChangingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingEventFunction, void*>> EventHandlingSimplifier::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingExtendedEventFunction, void*>> EventHandlingSimplifier::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingExtendedEventCallback(function, data, add);
}

IDObject<std::pair<TextInputEventFunction, void*>> EventHandlingSimplifier::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextInputEventCallback(function, data, add);
}

IDObject<std::pair<MouseMotionEventFunction, void*>> EventHandlingSimplifier::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseMotionEventCallback(function, data, add);
}

IDObject<std::pair<MouseButtonEventFunction, void*>> EventHandlingSimplifier::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseButtonEventCallback(function, data, add);
}

IDObject<std::pair<MouseWheelEventFunction, void*>> EventHandlingSimplifier::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseWheelEventCallback(function, data, add);
}

IDObject<std::pair<JoyAxisEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickAxisEventCallback(function, data, add);
}

IDObject<std::pair<JoyBallEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBallEventCallback(function, data, add);
}

IDObject<std::pair<JoyHatEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickHatEventCallback(function, data, add);
}

IDObject<std::pair<JoyButtonEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickButtonEventCallback(function, data, add);
}

IDObject<std::pair<JoyDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickDeviceEventCallback(function, data, add);
}

IDObject<std::pair<JoyBatteryEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBatteryEventCallback(function, data, add);
}

IDObject<std::pair<ControllerAxisEventFunction, void*>> EventHandlingSimplifier::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerAxisEventCallback(function, data, add);
}

IDObject<std::pair<ControllerButtonEventFunction, void*>> EventHandlingSimplifier::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerButtonEventCallback(function, data, add);
}

IDObject<std::pair<ControllerDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerDeviceEventCallback(function, data, add);
}

IDObject<std::pair<ControllerTouchpadEventFunction, void*>> EventHandlingSimplifier::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerTouchpadEventCallback(function, data, add);
}

IDObject<std::pair<ControllerSensorEventFunction, void*>> EventHandlingSimplifier::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerSensorEventCallback(function, data, add);
}

IDObject<std::pair<AudioDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAudioDeviceEventCallback(function, data, add);
}

IDObject<std::pair<TouchFingerEventFunction, void*>> EventHandlingSimplifier::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTouchFingerEventCallback(function, data, add);
}

IDObject<std::pair<MultiGestureEventFunction, void*>> EventHandlingSimplifier::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMultiGestureEventCallback(function, data, add);
}

IDObject<std::pair<DollarGestureEventFunction, void*>> EventHandlingSimplifier::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDollarGestureEventCallback(function, data, add);
}

IDObject<std::pair<ClipboardEventFunction, void*>> EventHandlingSimplifier::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterClipboardEventCallback(function, data, add);
}

IDObject<std::pair<DropEventFunction, void*>> EventHandlingSimplifier::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDropEventCallback(function, data, add);
}

IDObject<std::pair<SensorEventFunction, void*>> EventHandlingSimplifier::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterSensorEventCallback(function, data, add);
}

IDObject<std::pair<UserEventFunction, void*>> EventHandlingSimplifier::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
{
	return _internal.RegisterUserEventCallback(function, data, add);
}

IDObject<std::pair<RenderTargetsResetEventFunction, void*>> EventHandlingSimplifier::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderTargetsResetEventCallback(function, data, add);
}

IDObject<std::pair<RenderDeviceResetEventFunction, void*>> EventHandlingSimplifier::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderDeviceResetEventCallback(function, data, add);
}

bool EventHandlingSimplifier::UnRegisterQuitEventCallback(IDObject<std::pair<QuitEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterQuitEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppTerminatingEventCallback(IDObject<std::pair<AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppTerminatingEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppLowMemoryEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppWillEnterBackgroundEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppDidEnterBackgroundEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppWillEnterForegroundEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAppDidEnterForegroundEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterLocaleChangedEventCallback(IDObject<std::pair<LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterLocaleChangedEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterDisplayEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterWindowEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterKeyboardEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterKeymapChangeEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterTextEditingEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterTextEditingExtendedEventCallback(IDObject<std::pair<TextEditingExtendedEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterTextEditingExtendedEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterTextInputEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterMouseMotionEventCallback(IDObject<std::pair<MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterMouseMotionEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterMouseButtonEventCallback(IDObject<std::pair<MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterMouseButtonEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterMouseWheelEventCallback(IDObject<std::pair<MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterMouseWheelEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyAxisEventCallback(IDObject<std::pair<JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyAxisEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyBallEventCallback(IDObject<std::pair<JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyBallEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyHatEventCallback(IDObject<std::pair<JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyHatEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyButtonEventCallback(IDObject<std::pair<JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyButtonEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyDeviceEventCallback(IDObject<std::pair<JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyDeviceEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterJoyBatteryEventCallback(IDObject<std::pair<JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterJoyBatteryEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterControllerAxisEventCallback(IDObject<std::pair<ControllerAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterControllerAxisEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterControllerButtonEventCallback(IDObject<std::pair<ControllerButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterControllerButtonEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterControllerDeviceEventCallback(IDObject<std::pair<ControllerDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterControllerDeviceEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterControllerTouchpadEventCallback(IDObject<std::pair<ControllerTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterControllerTouchpadEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterControllerSensorEventCallback(IDObject<std::pair<ControllerSensorEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterControllerSensorEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterAudioDeviceEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterTouchFingerEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterMultiGestureEventCallback(IDObject<std::pair<MultiGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterMultiGestureEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterDollarGestureEventCallback(IDObject<std::pair<DollarGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterDollarGestureEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterClipboardEventCallback(IDObject<std::pair<ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterClipboardEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterDropEventCallback(IDObject<std::pair<DropEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterDropEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterSensorEventCallback(IDObject<std::pair<SensorEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterSensorEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterUserEventCallback(IDObject<std::pair<UserEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterUserEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterRenderTargetsResetEventCallback(ID, throwOnIDNotFound);
}

bool EventHandlingSimplifier::UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound)
{
	return _internal.UnRegisterRenderDeviceResetEventCallback(ID, throwOnIDNotFound);
}
