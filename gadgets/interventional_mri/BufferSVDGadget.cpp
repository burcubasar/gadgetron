#include "BufferSVDGadget.h"
#include "Context.h"
#include "Channel.h"
#include "Types.h"
#include "hoNDArray.h"
#include "hoNDKLT.h"

#include <tuple>
#include <array>

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
	  auto [header, data, meta] = image_buffer[i];
            images(slice,slice,slice,slice,i) = data;
        }

	return images;
    }
}
*/

namespace Gadgetron::Core {

    BufferSVDGadget::BufferSVDGadget(
            const Context &context,
            const std::unordered_map<std::string, std::string> &props
    ) : ChannelGadget(props), context(context) {}

  void BufferSVDGadget::process(InputChannel<std::deque<Image<float>>> &in, OutputChannel &out) {
    
    for (auto buffer : in) {
          
        hoNDKLT<float> KLT;
        hoNDArray<float> PCs;
	
	using namespace Gadgetron::Indexing;		
        auto [header,tmp,meta] = buffer.front();
	out.push(Image<float> {header,tmp,meta});
        
	int numFrames = buffer.size();
	int numElems = tmp.size();
	
	//	hoNDArray<float> collected_data = combine_images(buffer);
	//  GDEBUG("data dims: %d\n",collected_data.size());
	//	out.push(Image<float> {header,tmp,meta});
	
	/*
	hoNDArray<float> collected_data = combine_images(buffer);
	GDEBUG("coll_data size %d\n", collected_data.size());
	GDEBUG("coll_data get size %d\n", collected_data.get_size(1));
	*/
	
	hoNDArray<float> data(1,numFrames*numElems);
	for (int x=0; x<buffer.size(); x++){
	 for (int i = 0; i<data_.size(); i++){
	   auto [header_,data_,meta_] = buffer[x];
	   data[x*i] = data_[i];
            }
	 )
         GDEBUG("size: %d\n:",data.dimensions());
       	  GDEBUG("size: %d\n:",data.size());
    

       	       
       			 
	//	KLT.prepare(data, (size_t)1, (size_t)1, false);
	//	KLT.transform(data,PCs,(size_t)1);

       
    }  
  }

    GADGETRON_GADGET_EXPORT(BufferSVDGadget);
}
