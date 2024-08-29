export module RunProgram.CreateRenderPassData;

import std;
import VulkanData;
import VulkanData.InstanceDependent;
import VulkanData.RenderPassData;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedRenderPassData;

import VulkanSimplifiers.Instance;
import VulkanSimplifiers.DeviceList;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.LogicalDeviceMain;
import VulkanSimplifiers.DeviceRenderPassData;

import VulkanSimplifiers.Common.ImageLayouts;
import VulkanSimplifiers.Common.DataFormatFlags;
import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.PipelineStageFlags;
import VulkanSimplifiers.Common.AccessFlags;

export void CreateRenderPassData(VulkanData& data);