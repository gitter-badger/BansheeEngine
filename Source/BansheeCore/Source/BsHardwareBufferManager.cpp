//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsHardwareBufferManager.h"
#include "BsVertexData.h"
#include "BsGpuBuffer.h"
#include "BsVertexDeclaration.h"
#include "BsGpuParamBlockBuffer.h"
#include "BsVertexDataDesc.h"
#include "BsGpuParams.h"

namespace bs 
{
    HardwareBufferManager::HardwareBufferManager()
    {
    }

    HardwareBufferManager::~HardwareBufferManager()
    {
    }

	SPtr<VertexDeclaration> HardwareBufferManager::createVertexDeclaration(const SPtr<VertexDataDesc>& desc)
    {
		VertexDeclaration* decl = new (bs_alloc<VertexDeclaration>()) VertexDeclaration(desc->createElements());

		SPtr<VertexDeclaration> declPtr = bs_core_ptr<VertexDeclaration>(decl);
		declPtr->_setThisPtr(declPtr);
		declPtr->initialize();

		return declPtr;
    }

	SPtr<VertexBuffer> HardwareBufferManager::createVertexBuffer(const VERTEX_BUFFER_DESC& desc)
	{
		SPtr<VertexBuffer> vbuf = bs_core_ptr<VertexBuffer>(new (bs_alloc<VertexBuffer>()) VertexBuffer(desc));
		vbuf->_setThisPtr(vbuf);
		vbuf->initialize();
		return vbuf;
	}

	SPtr<IndexBuffer> HardwareBufferManager::createIndexBuffer(const INDEX_BUFFER_DESC& desc)
	{
		SPtr<IndexBuffer> ibuf = bs_core_ptr<IndexBuffer>(new (bs_alloc<IndexBuffer>()) IndexBuffer(desc));
		ibuf->_setThisPtr(ibuf);
		ibuf->initialize();
		return ibuf;

	}

	SPtr<GpuParamBlockBuffer> HardwareBufferManager::createGpuParamBlockBuffer(UINT32 size, GpuParamBlockUsage usage)
	{
		SPtr<GpuParamBlockBuffer> paramBlockPtr = bs_core_ptr<GpuParamBlockBuffer>(new (bs_alloc<GpuParamBlockBuffer>()) GpuParamBlockBuffer(size, usage));
		paramBlockPtr->_setThisPtr(paramBlockPtr);
		paramBlockPtr->initialize();
		return paramBlockPtr;
	}

	SPtr<GpuBuffer> HardwareBufferManager::createGpuBuffer(const GPU_BUFFER_DESC& desc)
	{
		SPtr<GpuBuffer> gbuf = bs_core_ptr<GpuBuffer>(new (bs_alloc<GpuBuffer>()) GpuBuffer(desc));
		gbuf->_setThisPtr(gbuf);
		gbuf->initialize();

		return gbuf;
	}

	SPtr<GpuParams> HardwareBufferManager::createGpuParams(const SPtr<GpuPipelineParamInfo>& paramInfo)
    {
		GpuParams* params = new (bs_alloc<GpuParams>()) GpuParams(paramInfo);
		SPtr<GpuParams> paramsPtr = bs_core_ptr<GpuParams>(params);
		paramsPtr->_setThisPtr(paramsPtr);
		paramsPtr->initialize();

		return paramsPtr;
    }

	namespace ct
	{

	HardwareBufferManager::VertexDeclarationKey::VertexDeclarationKey(const List<VertexElement>& elements)
		:elements(elements)
	{ }


	size_t HardwareBufferManager::VertexDeclarationKey::HashFunction::operator()(const VertexDeclarationKey& v) const
	{
		size_t hash = 0;
		for(auto& entry : v.elements)
			hash_combine(hash, VertexElement::getHash(entry));

		return hash;
	}

	bool HardwareBufferManager::VertexDeclarationKey::EqualFunction::operator()(const VertexDeclarationKey& lhs, 
		const VertexDeclarationKey& rhs) const
	{
		if (lhs.elements.size() != rhs.elements.size())
			return false;

		size_t numElements = lhs.elements.size();
		auto iterLeft = lhs.elements.begin();
		auto iterRight = rhs.elements.begin();
		for(size_t i = 0; i < numElements; i++)
		{
			if (*iterLeft != *iterRight)
				return false;

			++iterLeft;
			++iterRight;
		}

		return true;
	}

	SPtr<IndexBuffer> HardwareBufferManager::createIndexBuffer(const INDEX_BUFFER_DESC& desc, 
		GpuDeviceFlags deviceMask)
	{
		SPtr<IndexBuffer> ibuf = createIndexBufferInternal(desc, deviceMask);
		ibuf->initialize();
		return ibuf;

	}

	SPtr<VertexBuffer> HardwareBufferManager::createVertexBuffer(const VERTEX_BUFFER_DESC& desc, 
		GpuDeviceFlags deviceMask)
	{
		SPtr<VertexBuffer> vbuf = createVertexBufferInternal(desc, deviceMask);
		vbuf->initialize();
		return vbuf;
	}

	SPtr<VertexDeclaration> HardwareBufferManager::createVertexDeclaration(const SPtr<VertexDataDesc>& desc, 
		GpuDeviceFlags deviceMask)
	{
		List<VertexElement> elements = desc->createElements();

		return createVertexDeclaration(elements, deviceMask);
	}

	SPtr<GpuParams> HardwareBufferManager::createGpuParams(const SPtr<GpuPipelineParamInfo>& paramInfo,
																   GpuDeviceFlags deviceMask)
    {
		SPtr<GpuParams> params = createGpuParamsInternal(paramInfo, deviceMask);
		params->initialize();

		return params;
    }

	SPtr<VertexDeclaration> HardwareBufferManager::createVertexDeclaration(const List<VertexElement>& elements,
		GpuDeviceFlags deviceMask)
	{
		VertexDeclarationKey key(elements);

		auto iterFind = mCachedDeclarations.find(key);
		if (iterFind != mCachedDeclarations.end())
			return iterFind->second;

		SPtr<VertexDeclaration> declPtr = createVertexDeclarationInternal(elements, deviceMask);
		declPtr->initialize();

		mCachedDeclarations[key] = declPtr;
		return declPtr;
	}

	SPtr<GpuParamBlockBuffer> HardwareBufferManager::createGpuParamBlockBuffer(UINT32 size, 
		GpuParamBlockUsage usage, GpuDeviceFlags deviceMask)
	{
		SPtr<GpuParamBlockBuffer> paramBlockPtr = createGpuParamBlockBufferInternal(size, usage, deviceMask);
		paramBlockPtr->initialize();

		return paramBlockPtr;
	}

	SPtr<GpuBuffer> HardwareBufferManager::createGpuBuffer(const GPU_BUFFER_DESC& desc,
		GpuDeviceFlags deviceMask)
	{
		SPtr<GpuBuffer> gbuf = createGpuBufferInternal(desc, deviceMask);
		gbuf->initialize();

		return gbuf;
	}

	SPtr<VertexDeclaration> HardwareBufferManager::createVertexDeclarationInternal(
		const List<VertexElement>& elements, GpuDeviceFlags deviceMask)
	{
		VertexDeclaration* decl = new (bs_alloc<VertexDeclaration>()) VertexDeclaration(elements, deviceMask);

		SPtr<VertexDeclaration> ret = bs_shared_ptr<VertexDeclaration>(decl);
		ret->_setThisPtr(ret);

		return ret;
	}

	SPtr<GpuParams> HardwareBufferManager::createGpuParamsInternal(
		const SPtr<GpuPipelineParamInfo>& paramInfo, GpuDeviceFlags deviceMask)
    {
		GpuParams* params = new (bs_alloc<GpuParams>()) GpuParams(paramInfo, deviceMask);
		SPtr<GpuParams> paramsPtr = bs_shared_ptr<GpuParams>(params);
		paramsPtr->_setThisPtr(paramsPtr);

		return paramsPtr;
    }
	}
}
