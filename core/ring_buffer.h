/*************************************************************************/
/*  ring_buffer.h                                                        */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2015 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "vector.h"

template <typename T>
class RingBuffer {

	Vector<T> data;
	int read_pos;
	int write_pos;
	int size_mask;
	
	inline int inc(int& p_var, int p_size) {
		int ret = p_var;
		p_var += p_size;
		p_var = p_var&size_mask;
		return ret;
	};
	
public:

	T read() {
		ERR_FAIL_COND_V(space_left() < 1, T());
		return data[inc(read_pos, 1)];
	};
	
	int read(T* p_buf, int p_size, bool p_advance=true) {
		int left = data_left();
		p_size = MIN(left, p_size);
		int pos = read_pos;
		int to_read = p_size;
		int dst = 0;
		while(to_read) {
			int end = pos + to_read;
			end = MIN(end, size());
			int total = end - pos;
			for (int i=0; i<total; i++) {
				p_buf[dst++] = data[pos + i];
			};
			to_read -= total;
			pos = 0;
		};
		if (p_advance) {
			inc(read_pos, p_size);
		};
		return p_size;
	};

	int copy(T* p_buf, int p_offset, int p_size) {
		
		int left = data_left();
		if ((p_offset+p_size)>left) {
			p_size-=left-p_offset;
			if (p_size<=0)
				return 0;
		}
		p_size = MIN(left, p_size);
		int pos = read_pos;
		inc(pos,p_offset);
		int to_read = p_size;
		int dst = 0;
		while(to_read) {
			int end = pos + to_read;
			end = MIN(end, size());
			int total = end - pos;
			for (int i=0; i<total; i++) {
				p_buf[dst++] = data[pos + i];
			};
			to_read -= total;
			pos = 0;
		};
		return p_size;
	};

	inline int advance_read(int p_n) {
		p_n = MIN(p_n, data_left());
		inc(read_pos, p_n);
		return p_n;
	};
	
	Error write(const T& p_v) {
		ERR_FAIL_COND_V( space_left() < 1, FAILED);
		data[inc(write_pos, 1)] = p_v;
		return OK;
	};
	
	int write(const T* p_buf, int p_size) {
		
		int left = space_left();
		p_size = MIN(left, p_size);
		
		int pos = write_pos;
		int to_write = p_size;
		int src = 0;
		while (to_write) {

			int end = pos + to_write;
			end = MIN(end, size());
			int total = end - pos;
			
			for (int i=0; i<total; i++) {
				data[pos+i] = p_buf[src++];
			};
			to_write -= total;
			pos = 0;
		};

		inc(write_pos, p_size);
		return p_size;
	};
	
	inline int space_left() {
		int left = read_pos - write_pos;
		if (left < 0) {
			return size() + left;
		};
		if (left == 0) {
			return size();
		};
		return left;
	};
	inline int data_left() {
		return size() - space_left();
	};
	
	inline int size() {
		return data.size();
	};
	
	void resize(int p_power) {
		int old_size = size();
		int new_size = 1<<p_power;
		int mask = new_size - 1;
		data.resize(1<<p_power);
		if (old_size < new_size && read_pos > write_pos) {
			for (int i=0; i<write_pos; i++) {
				data[(old_size + i)&mask] = data[i];
			};
			write_pos = (old_size + write_pos) & mask;
		} else {
			read_pos = read_pos & mask;
			write_pos = write_pos & mask;
		};
		
		size_mask = mask;
	};
	
	RingBuffer<T>(int p_power=0) {
		read_pos = 0;
		write_pos = 0;
		resize(p_power);
	};
	~RingBuffer<T>() {};
};

#endif
