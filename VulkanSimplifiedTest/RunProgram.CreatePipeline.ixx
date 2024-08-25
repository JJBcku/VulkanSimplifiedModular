export module RunProgram.CreatePipeline;

import std;

import VulkanData;
import VulkanData.Basic;
import VulkanData.SharedData;
import VulkanData.InstanceDependent;
import VulkanData.DeviceDependent;
import VulkanData.PipelineLayoutData;

import VulkanSimplifiers.Main;
import VulkanSimplifiers.SharedDataList;
import VulkanSimplifiers.SharedPipelineData;
import VulkanSimplifiers.SharedPipelineData.Data;

import VulkanSimplifiers.Window;
import VulkanSimplifiers.WindowList;

export void CreatePipeline(VulkanData& data);