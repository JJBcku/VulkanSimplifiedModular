export module RunProgram.RunFrame;

import std;

import MainSettings;
import VulkanData;

import VulkanData.Basic;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.NIRCommandPool;
import VulkanSimplifiers.PrimaryNIRCommandBuffer;

import VulkanSimplifiers.CommandPoolQFGroupList.Data;

export void RunFrame(VulkanData& data, size_t frameNumber);