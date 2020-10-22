#pragma once

#include <strix/net/buffer/Buffer.h>

#include <list>
#include <vector>
#include <mutex>

namespace strix { namespace net { namespace buffer {
	
struct BufferChunk
{
	uint8_t *data;
};

class ListBuffer : public Buffer
{
public:
	ListBuffer();
	ListBuffer(size_t size);
	virtual ~ListBuffer();

	void Init(size_t size) override;

	bool Ensure(size_t size) override;

	size_t GetReadableSize() const override;

	size_t GetWritableSize() const override;

	size_t Read(uint8_t *buf, size_t length) override;
	
	size_t Write(const uint8_t *data, size_t length) override;

	const std::vector<RawBuffer> GetReadRawBuffers() override;

	const std::vector<RawBuffer> GetWriteRawBuffers() override;

	const std::vector<RawBuffer> GetReadRawBuffers(RawBuffer *headerRawBuffer) override;

	const std::vector<RawBuffer> GetWriteRawBuffers(RawBuffer *headerRawBuffer) override;

	size_t GetReadPosition() const override;

	bool SetReadPosition(size_t position) override;

	size_t GetWritePosition() const override;

	bool SetWritePosition(size_t position) override;

	bool IsReadMarked() const override;
	
	bool IsWriteMarked() const override;

	bool MarkRead() override;

	bool MarkWrite() override;

	bool ResetRead() override;

	bool ResetWrite() override;

	bool UnmarkRead() override;

	bool UnmarkWrite() override;

private:
	typedef std::list<BufferChunk*> ChunkList;

	class BufferIndex
	{
	public:
		BufferIndex();

		void Init(ChunkList &chunkList);

		void Advance(size_t size);

		int GetOffset() const {
			return m_offset;
		}

		BufferChunk *GetChunk() const {
			return *m_it;
		}

		size_t CalcPositionFrom(const BufferIndex &from) const {
			int position = GetPosition() - from.GetPosition();
			return position;
		}

		bool IsSameChunk(const BufferIndex &rhs) const {
			return (m_chunkIndex == rhs.m_chunkIndex);
		}

		bool operator<(const BufferIndex &rhs) const {
			int position = static_cast<int>(CalcPositionFrom(rhs));
			return position < 0;
		}

		bool operator>(const BufferIndex &rhs) const {
			int position = static_cast<int>(CalcPositionFrom(rhs));
			return position > 0;
		}

		bool operator<=(const BufferIndex &rhs) const {
			return !operator>(rhs);
		}

		bool operator>=(const BufferIndex &rhs) const {
			return !operator<(rhs);
		}

		bool operator==(const BufferIndex &rhs) const {
			return GetPosition() == rhs.GetPosition();
		}

		bool operator!=(const BufferIndex &rhs) const {
			return !operator==(rhs);
		}

		ChunkList::iterator m_it;
		volatile int m_offset;
		volatile int m_chunkIndex;

	private:
		int GetPosition() const;
	};
	
	typedef int Flags;
	static const int Flag_ReadMarked  = 0x01;
	static const int Flag_WriteMarked = 0x02;

	size_t CalcReadableSize() const;

	size_t CalcWritableSize() const;

	size_t _GetReadableSize() const;

	size_t _GetWritableSize() const;
	
	size_t _GetReadPosition() const;

	size_t _GetWritePosition() const;

	bool _IsReadMarked() const;
	
	bool _IsWriteMarked() const;

	std::vector<RawBuffer> GetRawBuffers(const ListBuffer::BufferIndex &startIndex, const ListBuffer::BufferIndex &endIndex);

	std::vector<RawBuffer> GetRawBuffers(RawBuffer *headerRawBuffer, const ListBuffer::BufferIndex &startIndex, const ListBuffer::BufferIndex &endIndex);

	bool ReadChunk(uint8_t *buf, size_t &length, const BufferIndex &endIndex);

	bool WriteChunk(const uint8_t *data, size_t &length, const BufferIndex &endIndex);

	void FreeUnusedChunks();

	BufferIndex GetReadEndIndex() const;

	BufferIndex GetWriteEndIndex() const;

	size_t CalcPosition(const BufferIndex &index, const BufferIndex &from) const;


	BufferIndex m_readIndex;
	BufferIndex m_writeIndex;
	BufferIndex m_readMark;
	BufferIndex m_writeMark;
	BufferIndex m_writeEnd;
	Flags m_flags;
	ChunkList m_chunkList;
	mutable std::mutex m_mutex;
	size_t m_readableSize;
	size_t m_writableSize;
};

} } }
