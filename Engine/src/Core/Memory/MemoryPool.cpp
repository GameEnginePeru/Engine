#include "Core/Memory/MemoryPool.h"

namespace Engine
{
	MemoryPool::MemoryPool(SIZE_T reserved, SIZE_T unitSize)
		: m_uReserved(reserved), m_uBlockSize(reserved * (unitSize + sizeof(MemoryUnit))), m_uUnitSize(unitSize)
	{
		OnCreate();
	}

	MemoryPool::~MemoryPool()
	{
		OnDestroy();
	}

	void MemoryPool::OnCreate()
	{
		m_pMemoryBlock = malloc(m_uBlockSize);
		if (m_pMemoryBlock)
		{
			for (SIZE_T i = 0; i < m_uReserved; i++)
			{
				MemoryUnit* pCurrentUnit = (MemoryUnit*)((char*)m_pMemoryBlock + i * (m_uUnitSize + sizeof(MemoryUnit)));

				pCurrentUnit->pPrev = nullptr;
				pCurrentUnit->pNext = m_pFreeUnit;

				if (m_pFreeUnit != nullptr)
				{
					m_pFreeUnit->pPrev = pCurrentUnit;
				}
				m_pFreeUnit = pCurrentUnit;
			}
		}
	}

	void MemoryPool::OnDestroy()
	{
		free(m_pMemoryBlock);
	}

	void* MemoryPool::Allocate()
	{
		if (m_pMemoryBlock == nullptr || m_pFreeUnit == nullptr)
		{
			return malloc(m_uUnitSize);
		}

		MemoryUnit* pCurrentUnit = m_pFreeUnit;
		m_pFreeUnit = pCurrentUnit->pNext;
		if (m_pFreeUnit != nullptr)
		{
			m_pFreeUnit->pPrev = nullptr;
		}

		pCurrentUnit->pNext = m_pAllocatedUnit;

		if (m_pAllocatedUnit != nullptr)
		{
			m_pAllocatedUnit->pPrev = pCurrentUnit;
		}

		m_pAllocatedUnit = pCurrentUnit;

		return (void*)((char*)pCurrentUnit + sizeof(MemoryUnit));
	}

	void MemoryPool::Free(void* ptr)
	{
		if (m_pMemoryBlock < ptr && ptr < (void*)((char*)m_pMemoryBlock + m_uBlockSize))
		{
			MemoryUnit* pCurrentUnit = (MemoryUnit*)((char*)ptr - sizeof(MemoryUnit));

			MemoryUnit* pPrev = pCurrentUnit->pPrev;
			MemoryUnit* pNext = pCurrentUnit->pNext;
			if (pPrev == nullptr)
			{
				m_pAllocatedUnit = pCurrentUnit->pNext;
			}
			else
			{
				pPrev->pNext = pNext;
			}
			if (pNext != nullptr)
			{
				pNext->pPrev = pPrev;
			}

			pCurrentUnit->pNext = m_pFreeUnit;
			if (m_pFreeUnit != nullptr)
			{
				m_pFreeUnit->pPrev = pCurrentUnit;
			}

			m_pFreeUnit = pCurrentUnit;
		}
		else
		{
			free(ptr);
		}
	}
}