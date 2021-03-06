/*
 * Copyright (c) 2011 Mark D. Hill and David A. Wood
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mem/ruby/slicc_interface/AbstractController.hh"
#include "mem/ruby/system/System.hh"

AbstractController::AbstractController(const Params *p)
    : ClockedObject(p), Consumer(this), m_fully_busy_cycles(0),
    m_request_count(0)
{
    m_version = p->version;
    m_transitions_per_cycle = p->transitions_per_cycle;
    m_buffer_size = p->buffer_size;
    m_recycle_latency = p->recycle_latency;
    m_number_of_TBEs = p->number_of_TBEs;
    m_is_blocking = false;
}

void
AbstractController::init()
{
    params()->ruby_system->registerAbstractController(this);
}

void
AbstractController::clearStats()
{
    m_requestProfileMap.clear();
    m_request_count = 0;

    m_delayHistogram.clear();

    uint32_t size = Network::getNumberOfVirtualNetworks();
    m_delayVCHistogram.resize(size);
    for (uint32_t i = 0; i < size; i++) {
        m_delayVCHistogram[i].clear();
    }
}

void
AbstractController::profileRequest(const std::string &request)
{
    m_request_count++;

    // if it doesn't exist, conveniently, it will be created with the
    // default value which is 0
    m_requestProfileMap[request]++;
}

void
AbstractController::profileMsgDelay(uint32_t virtualNetwork, Cycles delay)
{
    assert(virtualNetwork < m_delayVCHistogram.size());
    m_delayHistogram.add(delay);
    m_delayVCHistogram[virtualNetwork].add(delay);
}
