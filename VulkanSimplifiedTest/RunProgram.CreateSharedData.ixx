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

export void CreateSharedData(VulkanData& data);