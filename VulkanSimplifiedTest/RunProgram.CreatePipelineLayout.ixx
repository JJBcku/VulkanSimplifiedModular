export module RunProgram.CreatePipelineLayout;
import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.SharedData;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.SharedPipelineData;

export void CreatePipelineLayout(VulkanData& data);