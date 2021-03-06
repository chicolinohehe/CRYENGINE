// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.
#include "HlslParser.inl"

void HlslParser::SParserState::InitTables(EShaderType shaderType)
{
	// 0 -> keyword, 1 -> reserved word, 2 -> both, 3 -> intrinsic
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509568(v=vs.85).aspx
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509569(v=vs.85).aspx
	keyWords.add
	  ("AppendStructuredBuffer", 0)
	  ("asm", 0)
	  ("asm_fragment", 0)
	  ("auto", 1)
	  ("BlendState", 0)
	  ("bool", 0)
	  ("break", 0)
	  ("Buffer", 0)
	  ("ByteAddressBuffer", 0)
	  ("case", 2)
	  ("catch", 1)
	  ("char", 1)
	  ("cbuffer", 0)
	  ("centroid", 0)
	  ("class", 2)
	  ("const_cast", 1)
	  ("column_major", 0)
	  ("compile", 0)
	  ("compile_fragment", 0)
	  ("CompileShader", 0)
	  ("const", 0)
	  ("continue", 0)
	  ("ComputeShader", 0)
	  ("ConsumeStructuredBuffer", 0)
	  ("default", 0)
	  ("DepthStencilState", 0)
	  ("DepthStencilView", 0)
	  ("default", 1)
	  ("delete", 1)
	  ("dynamic_cast", 1)
	  ("discard", 0)
	  ("do", 0)
	  ("double", 0)
	  ("DomainShader", 0)
	  ("dword", 0)
	  ("else", 0)
	  ("enum", 1)
	  ("explicit", 1)
	  ("export", 0)
	  ("extern", 0)
	  ("false", 0)
	  ("float", 0)
	  ("for", 0)
	  ("friend", 1)
	  ("fxgroup", 0)
	  ("GeometryShader", 0)
	  ("goto", 1)
	  ("groupshared", 0)
	  ("half", 0)
	  ("HullShader", 0)
	  ("if", 0)
	  ("in", 0)
	  ("inline", 0)
	  ("inout", 0)
	  ("InputPatch", 0)
	  ("int", 0)
	  ("interface", 0)
	  ("line", 0)
	  ("lineadj", 0)
	  ("linear", 0)
	  ("LineStream", 0)
	  ("long", 1)
	  ("matrix", 0)
	  ("min16float", 0)
	  ("min16int", 0)
	  ("min12int", 0)
	  ("min16uint", 0)
	  ("mutable", 1)
	  ("namespace", 0)
	  ("new", 1)
	  ("nointerpolation", 0)
	  ("NULL", 0)
	  ("operator", 1)
	  ("out", 0)
	  ("OutputPatch", 0)
	  ("packoffset", 0)
	  ("pass", 0)
	  ("pixelfragment", 0)
	  ("PixelShader", 0)
	  ("point", 0)
	  ("PointStream", 0)
	  ("precise", 0)
	  ("private", 1)
	  ("protected", 1)
	  ("public", 1)
	  ("RasterizerState", 0)
	  ("reinterpret_cast", 1)
	  ("RenderTargetView", 0)
	  ("return", 0)
	  ("register", 0)
	  ("row_major", 0)
	  ("RWBuffer", 0)
	  ("RWByteAddressBuffer", 0)
	  ("RWStructuredBuffer", 0)
	  ("RWTexture1D", 0)
	  ("RWTexture1DArray", 0)
	  ("RWTexture2D", 0)
	  ("RWTexture2DArray", 0)
	  ("RWTexture3D", 0)
	  ("sample", 0)
	  ("sampler", 0)
	  ("SamplerState", 0)
	  ("SamplerComparisonState", 0)
	  ("shared", 0)
	  ("short", 1)
	  ("signed", 1)
	  ("sizeof", 1)
	  ("snorm", 0)
	  ("stateblock", 0)
	  ("stateblock_state", 0)
	  ("static", 0)
	  ("static_cast", 1)
	  ("string", 0)
	  ("struct", 0)
	  ("switch", 0)
	  ("StructuredBuffer", 0)
	  ("tbuffer", 0)
	  ("technique", 0)
	  ("technique10", 0)
	  ("technique11", 0)
	  ("template", 1)
	  ("texture", 0)
	  ("Texture1D", 0)
	  ("Texture1DArray", 0)
	  ("Texture2D", 0)
	  ("Texture2DArray", 0)
	  ("Texture2DMS", 0)
	  ("Texture2DMSArray", 0)
	  ("Texture3D", 0)
	  ("TextureCube", 0)
	  ("TextureCubeArray", 0)
	  ("this", 1)
	  ("throw", 1)
	  ("true", 0)
	  ("typedef", 0)
	  ("triangle", 0)
	  ("triangleadj", 0)
	  ("TriangleStream", 0)
	  ("try", 1)
	  ("typename", 1)
	  ("uint", 0)
	  ("uniform", 0)
	  ("union", 1)
	  ("unorm", 0)
	  ("unsigned", 2)
	  ("using", 1)
	  ("vector", 0)
	  ("vertexfragment", 0)
	  ("VertexShader", 0)
	  ("virtual", 1)
	  ("void", 0)
	  ("volatile", 0)
	  ("while", 0);
	keyWords.name("static_keywords");

	// Note: NOT case-sensitive, so all entries must be lower-case!
	// All names not mentioned here are treated as user-defined semantics
	if (shaderType == kShaderTypePixel)
	{
		// D3D9 PS compatibility
		systemValues.add
		  ("color", kSystemValueTarget | kSystemValueWithDigits | (7 << kSystemValueMaxDigitShift))
		  ("depth", kSystemValueDepth);
	}
	systemValues.add
	// D3D9 VS/PS compatibility
	  ("position", kSystemValuePosition | kSystemValueWithDigits | (0 << kSystemValueMaxDigitShift))
	  ("vpos", kSystemValuePosition)
	// SM4.0
	  ("sv_clipdistance", kSystemValueClipDistance | kSystemValueWithDigits | (1 << kSystemValueMaxDigitShift))
	  ("sv_culldistance", kSystemValueCullDistance | kSystemValueWithDigits | (1 << kSystemValueMaxDigitShift))
	  ("sv_coverage", kSystemValueCoverage)
	  ("sv_depth", kSystemValueDepth)
	  ("sv_depthgreaterequal", kSystemValueDepthGreaterEqual)
	  ("sv_depthlessequal", kSystemValueDepthLessEqual)
	  ("sv_instanceid", kSystemValueInstanceId)
	  ("sv_isfrontface", kSystemValueIsFrontFace)
	  ("sv_position", kSystemValuePosition)
	  ("sv_primitiveid", kSystemValuePrimitiveId)
	  ("sv_rendertargetarrayindex", kSystemValueRenderTargetArrayIndex)
	  ("sv_sampleindex", kSystemValueSampleIndex)
	  ("sv_target", kSystemValueTarget | kSystemValueWithDigits | (7 << kSystemValueMaxDigitShift))
	  ("sv_vertexid", kSystemValueVertexId)
	  ("sv_viewportarrayindex", kSystemValueViewportArrayIndex)
	// SM5.0
	  ("sv_dispatchthreadid", kSystemValueDispatchThreadId)
	  ("sv_domainlocation", kSystemValueDomainLocation)
	  ("sv_groupid", kSystemValueGroupId)
	  ("sv_groupindex", kSystemValueGroupIndex)
	  ("sv_groupthreadid", kSystemValueGroupThreadId)
	  ("sv_gsinstanceid", kSystemValueGsInstanceId)
	  ("sv_insidetessfactor", kSystemValueInsideTessFactor)
	  ("sv_outputcontrolpointid", kSystemValueOutputControlPointId)
	  ("sv_tessfactor", kSystemValueTessFactor)
	// SM5.1
	  ("sv_innercoverage", kSystemValueInnerCoverage)
	  ("sv_stencilref", kSystemValueStencilRef);
	systemValues.name("static_system_values");

	storageClass.add
	  ("extern", kStorageClassExtern)
	  ("precise", kStorageClassPrecise)
	  ("shared", kStorageClassShared)
	  ("groupshared", kStorageClassGroupShared)
	  ("static", kStorageClassStatic)
	  ("uniform", kStorageClassUniform)
	  ("volatile", kStorageClassVolatile);
	storageClass.name("static_storage_class");

	interpolationModifiers.add
	  ("linear", kInterpolationModifierLinear)
	  ("centroid", kInterpolationModifierCentroid)
	  ("nointerpolation", kInterpolationModifierNoInterpolation)
	  ("noperspective", kInterpolationModifierNoPerspective)
	  ("sample", kInterpolationModifierSample);
	interpolationModifiers.name("static_interpolation_modifiers");

	inputModifiers.add
	  ("in", kInputModifierIn)
	  ("out", kInputModifierOut)
	  ("inout", kInputModifierIn | kInputModifierOut)
	  ("uniform", kInputModifierUniform);
	inputModifiers.name("static_input_modifiers");

	object0Types.add
	  ("ByteAddressBuffer", kBaseTypeByteAddressBuffer)
	  ("RWByteAddressBuffer", kBaseTypeRWByteAddressBuffer)
	  ("RasterizerOrderedByteAddressBuffer", kBaseTypeRasterizerOrderedByteAddressBuffer)
	  ("sampler1D", kBaseTypeSampler1D)
	  ("sampler2D", kBaseTypeSampler2D)
	  ("sampler3D", kBaseTypeSampler3D)
	  ("samplerCUBE", kBaseTypeSamplerCUBE)
	  ("sampler_state", kBaseTypeSamplerState)
	  ("SamplerState", kBaseTypeSamplerState)
	  ("SamplerComparisonState", kBaseTypeSamplerComparisonState);
	object0Types.name("static_object0_types");

	object1Types.add
	  ("Buffer", kBaseTypeBuffer)
	  ("StructuredBuffer", kBaseTypeStructuredBuffer)
	  ("AppendStructuredBuffer", kBaseTypeAppendStructuredBuffer)
	  ("ConsumeStructuredBuffer", kBaseTypeConsumeStructuredBuffer)
	  ("Texture1D", kBaseTypeTexture1D)
	  ("Texture1DArray", kBaseTypeTexture1DArray)
	  ("Texture2D", kBaseTypeTexture2D)
	  ("Texture2DArray", kBaseTypeTexture2DArray)
	  ("Texture3D", kBaseTypeTexture3D)
	  ("TextureCube", kBaseTypeTextureCube)
	  ("TextureCubeArray", kBaseTypeTextureCubeArray)
	  ("RWBuffer", kBaseTypeRWBuffer)
	  ("RWStructuredBuffer", kBaseTypeRWStructuredBuffer)
	  ("RWTexture1D", kBaseTypeRWTexture1D)
	  ("RWTexture1DArray", kBaseTypeRWTexture1DArray)
	  ("RWTexture2D", kBaseTypeRWTexture2D)
	  ("RWTexture2DArray", kBaseTypeRWTexture2DArray)
	  ("RWTexture3D", kBaseTypeRWTexture3D)
	  ("RasterizerOrderedBuffer", kBaseTypeRasterizerOrderedBuffer)
	  ("RasterizerOrderedStructuredBuffer", kBaseTypeRasterizerOrderedStructuredBuffer)
	  ("RasterizerOrderedTexture1D", kBaseTypeRasterizerOrderedTexture1D)
	  ("RasterizerOrderedTexture1DArray", kBaseTypeRasterizerOrderedTexture1DArray)
	  ("RasterizerOrderedTexture2D", kBaseTypeRasterizerOrderedTexture2D)
	  ("RasterizerOrderedTexture2DArray", kBaseTypeRasterizerOrderedTexture2DArray)
	  ("RasterizerOrderedTexture3D", kBaseTypeRasterizerOrderedTexture3D);
	object1Types.name("static_object1_types");

	object2Types.add
	  ("Texture2DMS", kBaseTypeTexture2DMS)
	  ("Texture2DMSArray", kBaseTypeTexture2DMSArray);
	object2Types.name("static_object2_types");

	if (shaderType == kShaderTypeGeometry)
	{
		object1Types.add
		  ("PointStream", kBaseTypePointStream)
		  ("LineStream", kBaseTypeLineStream)
		  ("TriangleStream", kBaseTypeTriangleStream);
	}
	else if (shaderType == kShaderTypeHull)
	{
		object2Types.add
		  ("InputPatch", kBaseTypeInputPatch)
		  ("OutputPatch", kBaseTypeOutputPatch);
	}
	else if (shaderType == kShaderTypeDomain)
	{
		object2Types.add
		  ("OutputPatch", kBaseTypeOutputPatch);
	}

	objectMembers.add
	// Generic
	  ("GetDimensions", kGenericIntrinsicGetDimensions | kMemberTextureAll | kMemberBufferAll)
	  ("Load", kGenericIntrinsicLoad | (kMemberTextureAll & ~kMemberTextureCubeAll) | kMemberTextureRWAll | kMemberBuffer | kMemberByteAddressBuffer | kMemberStructuredBuffer | kMemberBufferRWAll)
	  ("<OPERATOR[]>", kGenericIntrinsicIndexOperator | kMemberTextureAll | kMemberTextureRWAll | kMemberBuffer | kMemberByteAddressBuffer | kMemberStructuredBuffer | kMemberBufferRWAll)
	//Texture
	  ("CalculateLevelOfDetail", kTextureIntrinsicCalculateLevelOfDetail | kMemberTextureAllNoMS)
	  ("CalculateLevelOfDetailUnclamped", kTextureIntrinsicCalculateLevelOfDetailUnclamped | kMemberTextureAllNoMS)
	  ("Gather", kTextureIntrinsicGather | kMemberTexture2DLike)
	  ("GatherRed", kTextureIntrinsicGatherRed | kMemberTexture2DLike)
	  ("GatherGreen", kTextureIntrinsicGatherGreen | kMemberTexture2DLike)
	  ("GatherBlue", kTextureIntrinsicGatherBlue | kMemberTexture2DLike)
	  ("GatherAlpha", kTextureIntrinsicGatherAlpha | kMemberTexture2DLike)
	  ("GatherCmpRed", kTextureIntrinsicGatherCmpRed | kMemberTexture2DLike)
	  ("GatherCmpGreen", kTextureIntrinsicGatherCmpGreen | kMemberTexture2DLike)
	  ("GatherCmpBlue", kTextureIntrinsicGatherCmpBlue | kMemberTexture2DLike)
	  ("GatherCmpAlpha", kTextureIntrinsicGatherCmpAlpha | kMemberTexture2DLike)
	  ("GetSamplePosition", kTextureIntrinsicGetSamplePosition | kMemberTexture2DAllMS)
	  ("mips", kTextureIntrinsicMipsOperator | kMemberTexture1DAll | kMemberTexture2DAllNoMS | kMemberTexture3D)
	  ("sample", kTextureIntrinsicSampleOperator | kMemberTexture2DAllMS)
	  ("Sample", kTextureIntrinsicSample | kMemberTextureAllNoMS)
	  ("SampleBias", kTextureIntrinsicSampleBias | kMemberTextureAllNoMS)
	  ("SampleCmp", kTextureIntrinsicSampleCmp | (kMemberTextureAllNoMS & ~kMemberTexture3D))
	  ("SampleCmpLevelZero", kTextureIntrinsicSampleCmpLevelZero | (kMemberTextureAllNoMS & ~kMemberTexture3D))
	  ("SampleGrad", kTextureIntrinsicSampleGrad | kMemberTextureAllNoMS)
	  ("SampleLevel", kTextureIntrinsicSampleLevel | kMemberTextureAllNoMS)
	// Buffer
	  ("Append", kBufferIntrinsicAppend | kMemberAppendStructuredBuffer | kMemberStreamOutput)
	  ("Consume", kBufferIntrinsicConsume | kMemberConsumeStructuredBuffer)
	  ("Load2", kBufferIntrinsicLoad2 | kMemberByteAddressBuffer | kMemberRWByteAddressBuffer)
	  ("Load3", kBufferIntrinsicLoad3 | kMemberByteAddressBuffer | kMemberRWByteAddressBuffer)
	  ("Load4", kBufferIntrinsicLoad4 | kMemberByteAddressBuffer | kMemberRWByteAddressBuffer)
	  ("Store", kBufferIntrinsicStore | kMemberRWByteAddressBuffer)
	  ("Store2", kBufferIntrinsicStore2 | kMemberRWByteAddressBuffer)
	  ("Store3", kBufferIntrinsicStore3 | kMemberRWByteAddressBuffer)
	  ("Store4", kBufferIntrinsicStore4 | kMemberRWByteAddressBuffer)
	  ("IncrementCounter", kBufferIntrinsicIncrementCounter | kMemberRWStructuredBuffer)
	  ("DecrementCounter", kBufferIntrinsicDecrementCounter | kMemberRWStructuredBuffer)
	  ("RestartStrip", kBufferIntrinsicRestartStrip | kMemberStreamOutput);
	objectMembers.name("static_object_members");

	if (shaderType == kShaderTypeDomain || shaderType == kShaderTypeHull)
	{
		attrDomain.add
		  ("\"tri\"", SAttribute::kDomainTri)
		  ("\"quad\"", SAttribute::kDomainQuad)
		  ("\"isoline\"", SAttribute::kDomainIsoLine);
		attrDomain.name("static_attribute_domain");
	}

	if (shaderType == kShaderTypeHull)
	{
		attrOutputTopology.add
		  ("\"point\"", SAttribute::kOutputTopologyPoint)
		  ("\"line\"", SAttribute::kOutputTopologyLine)
		  ("\"triangle_cw\"", SAttribute::kOutputTopologyTriangleCW)
		  ("\"triangle_ccw\"", SAttribute::kOutputTopologyTriangleCCW);
		attrOutputTopology.name("static_attribute_output_topology");

		attrPartitioning.add
		  ("\"integer\"", SAttribute::kPartitioningInteger)
		  ("\"fractional_even\"", SAttribute::kPartitioningFractionalEven)
		  ("\"fractional_odd\"", SAttribute::kPartitioningFractionalOdd)
		  ("\"pow2\"", SAttribute::kPartitioningPow2);
		attrPartitioning.name("static_attribute_partitioning");
	}

	if (shaderType == kShaderTypeGeometry)
	{
		geometryType.add
		  ("point", kGeometryTypePoint)
		  ("line", kGeometryTypeLine)
		  ("triangle", kGeometryTypeTriangle)
		  ("lineadj", kGeometryTypeLineAdj)
		  ("triangleadj", kGeometryTypeTriangleAdj);
		geometryType.name("static_geometry_type");
	}

	intrinsics.add
	  ("abort", kIntrinsicAbort)
	  ("abs", kIntrinsicAbs)
	  ("acos", kIntrinsicACos)
	  ("all", kIntrinsicAll)
	  ("AllMemoryBarrier", kIntrinsicAllMemoryBarrier)
	  ("AllMemoryBarrierWithGroupSync", kIntrinsicAllMemoryBarrierWithGroupSync)
	  ("any", kIntrinsicAny)
	  ("asdouble", kIntrinsicAsDouble)
	  ("asfloat", kIntrinsicAsFloat)
	  ("asin", kIntrinsicASin)
	  ("asint", kIntrinsicAsInt)
	  ("asuint", kIntrinsicAsUInt)
	  ("atan", kIntrinsicATan)
	  ("atan2", kIntrinsicATan2)
	  ("ceil", kIntrinsicCeil)
	  ("CheckAccessFullyMapped", kIntrinsicCheckAccessFullyMapped)
	  ("clamp", kIntrinsicClamp)
	  ("clip", kIntrinsicClip)
	  ("cos", kIntrinsicCos)
	  ("cosh", kIntrinsicCosH)
	  ("countbits", kIntrinsicCountBits)
	  ("cross", kIntrinsicCross)
	  ("D3DCOLORtoUBYTE4", kIntrinsicD3DCOLORtoUBYTE4)
	  ("ddx", kIntrinsicDDX)
	  ("ddx_coarse", kIntrinsicDDXCoarse)
	  ("ddx_fine", kIntrinsicDDXFine)
	  ("ddy", kIntrinsicDDY)
	  ("ddy_coarse", kIntrinsicDDYCoarse)
	  ("ddy_fine", kIntrinsicDDYFine)
	  ("degrees", kIntrinsicDegrees)
	  ("determinant", kIntrinsicDeterminant)
	  ("DeviceMemoryBarrier", kIntrinsicDeviceMemoryBarrier)
	  ("DeviceMemoryBarrierWithGroupSync", kIntrinsicDeviceMemoryBarrierWithGroupSync)
	  ("distance", kIntrinsicDistance)
	  ("dot", kIntrinsicDot)
	  ("dst", kIntrinsicDst)
	  ("errorf", kIntrinsicErrorF)
	  ("EvaluateAttributeAtCentroid", kIntrinsicEvaluateAttributeAtCentroid)
	  ("EvaluateAttributeAtSample", kIntrinsicEvaluateAttributeAtSample)
	  ("EvaluateAttributeSnapped", kIntrinsicEvaluateAttributeSnapped)
	  ("exp", kIntrinsicExp)
	  ("exp2", kIntrinsicExp2)
	  ("f16tof32", kIntrinsicF16ToF32)
	  ("f32tof16", kIntrinsicF32ToF16)
	  ("faceforward", kIntrinsicFaceForward)
	  ("firstbithigh", kIntrinsicFirstBitHigh)
	  ("firstbitlow", kIntrinsicFirstBitLow)
	  ("floor", kIntrinsicFloor)
	  ("fma", kIntrinsicFMA)
	  ("fmod", kIntrinsicFMod)
	  ("frac", kIntrinsicFrac)
	  ("frexp", kIntrinsicFrExp)
	  ("fwidth", kIntrinsicFWidth)
	  ("GetRenderTargetSampleCount", kIntrinsicGetRenderTargetSampleCount)
	  ("GetRenderTargetSamplePosition", kIntrinsicGetRenderTargetSamplePosition)
	  ("GroupMemoryBarrier", kIntrinsicGroupMemoryBarrier)
	  ("GroupMemoryBarrierWithGroupSync", kIntrinsicGroupMemoryBarrierWithGroupSync)
	  ("InterlockedAdd", kIntrinsicInterlockedAdd)
	  ("InterlockedAnd", kIntrinsicInterlockedAnd)
	  ("InterlockedCompareExchange", kIntrinsicInterlockedCompareExchange)
	  ("InterlockedCompareStore", kIntrinsicInterlockedCompareStore)
	  ("InterlockedExchange", kIntrinsicInterlockedExchange)
	  ("InterlockedMax", kIntrinsicInterlockedMax)
	  ("InterlockedMin", kIntrinsicInterlockedMin)
	  ("InterlockedOr", kIntrinsicInterlockedOr)
	  ("InterlockedXor", kIntrinsicInterlockedXor)
	  ("isfinite", kIntrinsicIsFinite)
	  ("isinf", kIntrinsicIsInf)
	  ("isnan", kIntrinsicIsNAN)
	  ("ldexp", kIntrinsicLdExp)
	  ("length", kIntrinsicLength)
	  ("lerp", kIntrinsicLerp)
	  ("lit", kIntrinsicLit)
	  ("log", kIntrinsicLog)
	  ("log10", kIntrinsicLog10)
	  ("log2", kIntrinsicLog2)
	  ("mad", kIntrinsicMad)
	  ("max", kIntrinsicMax)
	  ("min", kIntrinsicMin)
	  ("modf", kIntrinsicModF)
	  ("msad4", kIntrinsicMSad4)
	  ("mul", kIntrinsicMul)
	  ("noise", kIntrinsicNoise)
	  ("normalize", kIntrinsicNormalize)
	  ("pow", kIntrinsicPow)
	  ("printf", kIntrinsicPrintF)
	  ("Process2DQuadTessFactorsAvg", kIntrinsicProcess2DQuadTessFactorsAvg)
	  ("Process2DQuadTessFactorsMax", kIntrinsicProcess2DQuadTessFactorsMax)
	  ("Process2DQuadTessFactorsMin", kIntrinsicProcess2DQuadTessFactorsMin)
	  ("ProcessIsolineTessFactors", kIntrinsicProcessIsolineTessFactors)
	  ("ProcessQuadTessFactorsAvg", kIntrinsicProcessQuadTessFactorsAvg)
	  ("ProcessQuadTessFactorsMax", kIntrinsicProcessQuadTessFactorsMax)
	  ("ProcessQuadTessFactorsMin", kIntrinsicProcessQuadTessFactorsMin)
	  ("ProcessTriTessFactorsAvg", kIntrinsicProcessTriTessFactorsAvg)
	  ("ProcessTriTessFactorsMax", kIntrinsicProcessTriTessFactorsMax)
	  ("ProcessTriTessFactorsMin", kIntrinsicProcessTriTessFactorsMin)
	  ("radians", kIntrinsicRadians)
	  ("rcp", kIntrinsicRcp)
	  ("reflect", kIntrinsicReflect)
	  ("refract", kIntrinsicRefract)
	  ("reversebits", kIntrinsicReverseBits)
	  ("round", kIntrinsicRound)
	  ("rsqrt", kIntrinsicRSqrt)
	  ("saturate", kIntrinsicSaturate)
	  ("sign", kIntrinsicSign)
	  ("sin", kIntrinsicSin)
	  ("sincos", kIntrinsicSinCos)
	  ("sinh", kIntrinsicSinH)
	  ("smoothstep", kIntrinsicSmoothStep)
	  ("sqrt", kIntrinsicSqrt)
	  ("step", kIntrinsicStep)
	  ("tan", kIntrinsicTan)
	  ("tanh", kIntrinsicTanH)
	  ("tex1D", kIntrinsicTex1D)
	  ("tex1Dbias", kIntrinsicTex1DBias)
	  ("tex1Dgrad", kIntrinsicTex1DGrad)
	  ("tex1Dlod", kIntrinsicTex1DLod)
	  ("tex1Dproj", kIntrinsicTex1DProj)
	  ("tex2D", kIntrinsicTex2D)
	  ("tex2Dbias", kIntrinsicTex2DBias)
	  ("tex2Dgrad", kIntrinsicTex2DGrad)
	  ("tex2Dlod", kIntrinsicTex2DLod)
	  ("tex2Dproj", kIntrinsicTex2DProj)
	  ("tex3D", kIntrinsicTex3D)
	  ("tex3Dbias", kIntrinsicTex3DBias)
	  ("tex3Dgrad", kIntrinsicTex3DGrad)
	  ("tex3Dlod", kIntrinsicTex3DLod)
	  ("tex3Dproj", kIntrinsicTex3DProj)
	  ("texCUBE", kIntrinsicTexCube)
	  ("texCUBEbias", kIntrinsicTexCubeBias)
	  ("texCUBEgrad", kIntrinsicTexCubeGrad)
	  ("texCUBElod", kIntrinsicTexCubeLod)
	  ("texCUBEproj", kIntrinsicTexCubeProj)
	  ("transpose", kIntrinsicTranspose)
	  ("trunc", kIntrinsicTrunc)
	  ("WaveOnce", kIntrinsicWaveOnce)
	  ("WaveGetLaneCount", kIntrinsicWaveGetLaneCount)
	  ("WaveGetLaneIndex", kIntrinsicWaveGetLaneIndex)
	  ("WaveIsHelperLane", kIntrinsicWaveIsHelperLane)
	  ("WaveAnyTrue", kIntrinsicWaveAnyTrue)
	  ("WaveAllTrue", kIntrinsicWaveAllTrue)
	  ("WaveAllEqual", kIntrinsicWaveAllEqual)
	  ("WaveBallot", kIntrinsicWaveBallot)
	  ("WaveReadLaneAt", kIntrinsicWaveReadLaneAt)
	  ("WaveReadFirstLane", kIntrinsicWaveReadFirstLane)
	  ("WaveAllSum", kIntrinsicWaveAllSum)
	  ("WaveAllProduct", kIntrinsicWaveAllProduct)
	  ("WaveAllBitAnd", kIntrinsicWaveAllBitAnd)
	  ("WaveAllBitOr", kIntrinsicWaveAllBitOr)
	  ("WaveAllBitXor", kIntrinsicWaveAllBitXor)
	  ("WaveAllMin", kIntrinsicWaveAllMin)
	  ("WaveAllMax", kIntrinsicWaveAllMax)
	  ("WavePrefixSum", kIntrinsicWavePrefixSum)
	  ("WavePrefixProduct", kIntrinsicWavePrefixProduct)
	  ("WaveGetOrderedIndex", kIntrinsicWaveGetOrderedIndex)
	  ("GlobalOrderedCountIncrement", kIntrinsicGlobalOrderedCountIncrement)
	  ("QuadReadLaneAt", kIntrinsicQuadReadLaneAt)
	  ("QuadSwapX", kIntrinsicQuadSwapX)
	  ("QuadSwapY", kIntrinsicQuadSwapY);
	intrinsics.name("static_intrinsics");

	swizzles.add
	  ("x", kSwizzleX | kSwizzleCategoryXYZW)
	  ("y", kSwizzleY | kSwizzleCategoryXYZW)
	  ("z", kSwizzleZ | kSwizzleCategoryXYZW)
	  ("w", kSwizzleW | kSwizzleCategoryXYZW)
	  ("r", kSwizzleR | kSwizzleCategoryRGBA)
	  ("g", kSwizzleG | kSwizzleCategoryRGBA)
	  ("b", kSwizzleB | kSwizzleCategoryRGBA)
	  ("a", kSwizzleA | kSwizzleCategoryRGBA)
	  ("_m00", kSwizzleM00 | kSwizzleCategory_MXX)
	  ("_m01", kSwizzleM01 | kSwizzleCategory_MXX)
	  ("_m02", kSwizzleM02 | kSwizzleCategory_MXX)
	  ("_m03", kSwizzleM03 | kSwizzleCategory_MXX)
	  ("_m10", kSwizzleM10 | kSwizzleCategory_MXX)
	  ("_m11", kSwizzleM11 | kSwizzleCategory_MXX)
	  ("_m12", kSwizzleM12 | kSwizzleCategory_MXX)
	  ("_m13", kSwizzleM13 | kSwizzleCategory_MXX)
	  ("_m20", kSwizzleM20 | kSwizzleCategory_MXX)
	  ("_m21", kSwizzleM21 | kSwizzleCategory_MXX)
	  ("_m22", kSwizzleM22 | kSwizzleCategory_MXX)
	  ("_m23", kSwizzleM23 | kSwizzleCategory_MXX)
	  ("_m30", kSwizzleM30 | kSwizzleCategory_MXX)
	  ("_m31", kSwizzleM31 | kSwizzleCategory_MXX)
	  ("_m32", kSwizzleM32 | kSwizzleCategory_MXX)
	  ("_m33", kSwizzleM33 | kSwizzleCategory_MXX)
	  ("_11", kSwizzle11 | kSwizzleCategory_XX)
	  ("_12", kSwizzle12 | kSwizzleCategory_XX)
	  ("_13", kSwizzle13 | kSwizzleCategory_XX)
	  ("_14", kSwizzle14 | kSwizzleCategory_XX)
	  ("_21", kSwizzle21 | kSwizzleCategory_XX)
	  ("_22", kSwizzle22 | kSwizzleCategory_XX)
	  ("_23", kSwizzle23 | kSwizzleCategory_XX)
	  ("_24", kSwizzle24 | kSwizzleCategory_XX)
	  ("_31", kSwizzle31 | kSwizzleCategory_XX)
	  ("_32", kSwizzle32 | kSwizzleCategory_XX)
	  ("_33", kSwizzle33 | kSwizzleCategory_XX)
	  ("_34", kSwizzle34 | kSwizzleCategory_XX)
	  ("_41", kSwizzle41 | kSwizzleCategory_XX)
	  ("_42", kSwizzle42 | kSwizzleCategory_XX)
	  ("_43", kSwizzle43 | kSwizzleCategory_XX)
	  ("_44", kSwizzle44 | kSwizzleCategory_XX);
	swizzles.name("static_swizzles");
}
