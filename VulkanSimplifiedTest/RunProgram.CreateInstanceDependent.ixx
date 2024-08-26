export module RunProgram.CreateInstanceDependent;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.InstanceDependent;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.PhysicalDevice;
import VulkanSimplifiers.PhysicalDevice.Data;
import VulkanSimplifiers.LogicalDeviceCore.CreationData;
import VulkanSimplifiers.LogicalDeviceMain.CreationData;
import VulkanSimplifiers.WindowList.Data;

import VulkanSimplifiers.Common.DataFormatFlags;

export void CreateInstanceDependent(VulkanData& data);