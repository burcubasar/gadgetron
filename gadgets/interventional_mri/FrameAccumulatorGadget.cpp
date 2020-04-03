#include "FrameAccumulatorGadget.h"
#include "Context.h"
#include "Channel.h"
#include "Types.h"

#include "hoNDArray.h"

namespace {
    using namespace Gadgetron;
    using namespace Gadgetron::Core;
}

namespace Gadgetron::Core {

    FrameAccumulatorGadget::FrameAccumulatorGadget(
            const Context &context,
            const std::unordered_map<std::string, std::string> &props
    ) : ChannelGadget(props), context(context) {}

  void FrameAccumulatorGadget::process(InputChannel<Image<float>> &in, OutputChannel &out) {

        std::vector<Image<float>> buffer;

	for (int x = 0; x<10; x++){
	  buffer.emplace_back(in.pop());
     	}
	
        for (auto image : in) {
            buffer.emplace_back(image);
	  
	    if (buffer.size() ==10) { GDEBUG("buffer size=1\n");
                out.push(image);
	    }
        }
  }

    GADGETRON_GADGET_EXPORT(FrameAccumulatorGadget);
}
