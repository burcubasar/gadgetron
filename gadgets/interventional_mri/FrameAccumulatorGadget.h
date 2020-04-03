#pragma once

#include <vector>


#include "Types.h"
#include "Node.h"

namespace Gadgetron::Core {

    using buffer = std::vector<Image<float>>;

    class FrameAccumulatorGadget : public Core::ChannelGadget<Image<float>> {
    public:
        FrameAccumulatorGadget(const Core::Context &, const std::unordered_map<std::string, std::string> &);

        void process(Core::InputChannel<Image<float>> &in, Core::OutputChannel &out) override;

    private:
        const Core::Context context;
    };
}

