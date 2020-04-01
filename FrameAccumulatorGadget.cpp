#include "FrameAccumulatorGadget.h"
#include "ismrmrd/meta.h"
#include "mri_core_def.h"

#include <vector>

//#include "GadgetIsmrmrdReadWrite.h"

namespace Gadgetron{
  
  FrameAccumulatorGadget::~FrameAccumulatorGadget(){
     };
  
  
  //template <typename T>
  int FrameAccumulatorGadget::process_config(ACE_Message_Block* mb) {

    ISMRMRD::IsmrmrdHeader hdr;
    ISMRMRD::deserialize(mb->rd_ptr(),hdr);

    
	return GADGET_OK;
   }


  //template <typename T>
  int FrameAccumulatorGadget::process(GadgetContainerMessage<ISMRMRD::ImageHeader>* m1, GadgetContainerMessage< hoNDArray<float > >* m2) {

    // if (m1->getObjectPtr()->image_type == ISMRMRD::ISMRMRD_IMTYPE_MAGNITUDE) { //only operate on magnitude images for now
        // need 10 frames
       
        ISMRMRD::ImageHeader h;
        h = *(m1->getObjectPtr());

	float im;
	im = *(m2->getObjectPtr()->get_data_ptr());

	std::vector<float> buf_;

	
        buf_.push_back(im);
        header_.push_back(h);

        if(buf_.size()==10)
        {
	  GDEBUG("10 frames\n");

/*
            // SVD
            size_t NDim = buf_.get_number_of_dimensions();
            size_t N = buf_.get_size(NDim-1);

            size_t M = buf_.get_number_of_elements() / N;

            hoNDArray<T> data2D;
            data2D.create(M, N, const_cast<T*>(buf_.begin()));

            V_.create(N, N);
            E_.create(N, 1);
            Gadgetron::clear(V_);
            Gadgetron::clear(E_);

            size_t m, n;

            // compute and subtract mean from data
            hoNDArray<T> data2DNoMean;

            arma::Mat<T> Am;

                if (remove_mean)
                {
                    hoNDArray<T> dataMean(1, N);
                    Gadgetron::sum_over_dimension(data2D, dataMean, 0);

                    Gadgetron::scal((T)(1.0 / M), dataMean);

                    data2DNoMean.create(M, N);

                    for (n = 0; n < N; n++)
                    {
                        for (m = 0; m < M; m++)
                        {
                            data2DNoMean(m, n) = data2D(m, n) - dataMean(0, n);
                        }
                    }

                    Am = as_arma_matrix(data2DNoMean);
                }
                else

            //{
            Am = as_arma_matrix(data2D);
            //}

            arma::Mat<T> Vm = as_arma_matrix(V_);
            arma::Mat<T> Um;
            arma::Col<value_type> Sv;

            arma::svd_econ(Um, Sv, Vm, Am, 'r');

            for (n = 0; n < N; n++)
            {
                value_type v = Sv(n);
                E_(n) = v * v; // the E is eigen value, the square of singular value
            }


            // Discard irrelevant components
*/



            // pop the top one
	  // buf_.pop_back(buf_.begin());
            

	    
	} //buffer size =10


	// } //magnitude image 

     
            // send out result
            if (this->next()->putq(m1) < 0) {
                                 		GDEBUG("Failed to pass on data to next Gadget\n");
                                 		return GADGET_FAIL;
                                 	}
            m1->release();
            return GADGET_OK;
        
    }

   GADGET_FACTORY_DECLARE(FrameAccumulatorGadget)
    //GADGET_FACTORY_DECLARE(FrameAccumulatorGadgetUSHORT)
   // GADGET_FACTORY_DECLARE(FrameAccumulatorGadgetFLOAT)
}



