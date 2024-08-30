export module RunProgram.CreateSharedData;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.SharedData;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Common.ImageSampleFlags;
import VulkanSimplifiers.Common.ShaderTypeFlags;

export void CreateSharedData(VulkanData& data);