#pragma once

#include <vector>
#include <deque>
#include <tuple>

#include "Types.h"
#include "Node.h"
#include "hoNDKLT.h"

namespace Gadgetron::Core {

  //  using buffer = std::vector<Image<float>>;

  class BufferSVDGadget : public Core::ChannelGadget<std::deque<Image<float>>> {
    public:
        BufferSVDGadget(const Core::Context &, const std::unordered_map<std::string, std::string> &);

    void process(Core::InputChannel<std::deque<Image<float>>> &in, Core::OutputChannel &out) override;

    private:
        const Core::Context context;
    };
}

