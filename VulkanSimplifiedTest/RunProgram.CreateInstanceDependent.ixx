export module RunProgram.CreateInstanceDependent;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.InstanceDependent;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.PhysicalDevice;
import VulkanSimplifiers.LogicalDevice.Data;
import VulkanSimplifiers.WindowList.Data;

export void CreateInstanceDependent(VulkanData& data);