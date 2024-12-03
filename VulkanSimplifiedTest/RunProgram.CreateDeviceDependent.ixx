export module RunProgram.CreateDeviceDependent;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.LogicalDeviceCore;
import VulkanSimplifiers.CommandPoolList;
import VulkanSimplifiers.CommandPoolQFGroupList;
import VulkanSimplifiers.NIRCommandPool;
import VulkanSimplifiers.IRCommandPool;

import VulkanSimplifiers.Common.SurfaceData;

export void CreateDeviceDependent(VulkanData& data);