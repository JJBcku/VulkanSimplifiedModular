export module RunProgram.CreateRenderPassData;

import std;
import VulkanData;
import VulkanData.InstanceDependent;
import VulkanData.RenderPassData;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedRenderPassData;

export void CreateRenderPassData(VulkanData& data);