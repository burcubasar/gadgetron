#include "FrameAccumulatorGadget.h"
#include "Context.h"
#include "Channel.h"
#include "Types.h"
#include "hoNDArray.h"

#include <deque>
#include <tuple>

namespace {
    using namespace Gadgetron;
    using namespace Gadgetron::Core;
}
/*
namespace {

    hoNDArray<float> combine_images(const std::deque<Image<float>>& image_buffer){
        using namespace Gadgetron::Indexing;
        auto [header, data, meta] = image_buffer.front();
        
        std::vector<size_t> dimensions = data.dimensions();
        dimensions.push_back(image_buffer.size());

        hoNDArray<float> images(dimensions);
        for (int i = 0; image_buffer.size(); i++){
            auto [header, data, meta] = image_buffer.front();
            images(slice,slice,slice,slice, i) = data;
        }

        return images;

    }    
}
*/
namespace Gadgetron::Core {

    FrameAccumulatorGadget::FrameAccumulatorGadget(
            const Context &context,
            const std::unordered_map<std::string, std::string> &props
    ) : ChannelGadget(props), context(context) {}

  void FrameAccumulatorGadget::process(InputChannel<Image<float>> &in, OutputChannel &out) {

        std::deque<Image<float>> buffer;

	for (int x = 0; x<9; x++){
	  buffer.emplace_back(in.pop());
     	}
	
        for (auto image : in) {
            buffer.emplace_back(image);
	    if (buffer.size() == 10){
	       out.push(buffer);
	      /*  hoNDArray<float> collected_buffer = combine_images(buffer);
	       auto [header,im,meta] = buffer.front();
	       out.push(Image<float> {header,collected_buffer,meta});*/
	    }
            buffer.pop_front();
	}
  }

    GADGETRON_GADGET_EXPORT(FrameAccumulatorGadget);
}
