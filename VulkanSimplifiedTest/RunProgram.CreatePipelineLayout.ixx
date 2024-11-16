export module RunProgram.CreatePipelineLayout;
import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.SharedData;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;
import VulkanData.PipelineLayoutData;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.DeviceList.Data;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.DevicePipelineData;
import VulkanSimplifiers.DevicePipelineData.LayoutCreationData;
import VulkanSimplifiers.DevicePipelineData.Data;

export void CreatePipelineLayout(VulkanData& data);