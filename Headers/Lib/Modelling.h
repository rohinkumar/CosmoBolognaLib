/********************************************************************
 *  Copyright (C) 2010 by Federico Marulli                          *
 *  federico.marulli3@unibo.it                                      *
 *                                                                  *
 *  This program is free software; you can redistribute it and/or   *
 *  modify it under the terms of the GNU General Public License as  *
 *  published by the Free Software Foundation; either version 2 of  * 
 *  the License, or (at your option) any later version.             *
 *                                                                  *
 *  This program is distributed in the hope that it will be useful, *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of  *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   *
 *  GNU General Public License for more details.                    *
 *                                                                  *
 *  You should have received a copy of the GNU General Public       *
 *  License along with this program; if not, write to the Free      *
 *  Software Foundation, Inc.,                                      *
 *  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.       *
 ********************************************************************/

/**
 *  @file Headers/Lib/Modelling.h
 *
 *  @brief The class Modelling
 *
 *  This file defines the interface of the class
 *  Modelling, used for modelling any kind of measurements
 *
 *  @author Federico Marulli
 *
 *  @author federico.marulli3@unbo.it
 */

#ifndef __MODELLING__
#define __MODELLING__


#include "Likelihood.h"


// ===================================================================================================


namespace cosmobl {

  /**
   *  @brief The namespace of the functions and classes used to <B>
   *  model </B> any kind of measurements
   *  
   *  The \e modelling namespace contains all the functions and
   *  classes used for modelling any kind of measurements
   */
  namespace modelling {
    
    /**
     *  @class Modelling Modelling.h
     *  "Headers/Lib/Modelling.h"
     *
     *  @brief The class Modelling
     *
     *  This file defines the interface of the base class Modelling,
     *  used for modelling any kind of measurements
     *
     */
    class Modelling {

    protected:
    
      /// input data to be modelled
      shared_ptr<data::Data> m_data;

      /// input model
      shared_ptr<statistics::Model> m_model;

      /// likelihood
      shared_ptr<statistics::Likelihood> m_likelihood;
      
    public:
      
      /**
       *  @name Constructors/destructors
       */
      ///@{

      /**
       *  @brief default constuctor
       *  @return object of class Modelling
       */
      Modelling () {}

      /**
       *  @brief default destructor
       *  @return none
       */
      virtual ~Modelling () {}

      /**
       * @brief return the dataset
       * @return pointer to the current dataset
       */
      shared_ptr<data::Data> data () {return m_data;}

      /**
       * @brief return the model
       * @return pointer to the current model
       */    
      shared_ptr<statistics::Model> model () {return m_model;}

      /**
       * @brief return the likelihood
       * @return pointer to the current likelihood
       */    
      shared_ptr<statistics::Likelihood> likelihood () {return m_likelihood;}

      ///@}

      /**
       * @brief set the dataset
       *
       * @param dataset the dataset 
       *
       * @return none
       */
      void set_data (const shared_ptr<data::Data> dataset) { m_data = move(dataset);}

      /**
       * @brief set the model
       *
       * @param model the model
       *
       * @return none
       */    
      void set_model (const shared_ptr<statistics::Model> model) { m_model = move(model);}


      /**
       * @brief sample the likelihood and write
       * chains on a file
       *
       * @param xmin lower bound for the fit
       * @param xmax upper bound for the fit
       * @param likelihood_type type of likelihood
       * @param n_chains number of parallel chains
       * @param chain_size size of the chains
       * @param seed the seed for random number generation
       * @param dir_output output directory
       * @param chain_file output file
       * @param start starting position in the chains
       * @param stop final position in the chains
       * @param thin interval of parameter in output
       *
       * @return none
       */
      void sample_likelihood(double xmin, double xmax,const statistics::LikelihoodType likelihood_type, const int n_chains, const int chain_size, const int seed, const string dir_output, const string chain_file, const double start=0.5, const double stop=1, const int thin=1);

      /**
       * @brief sample the likelihood and write
       * chains on a file
       *
       * @param xmin lower bound for the fit
       * @param xmax upper bound for the fit
       * @param likelihood_type type of likelihood
       * @param loglikelihood_function the user-defined loglikelihood
       * function
       * @param cov 0 &rarr; do not use data covariance, 1 &rarr; use data covariance 
       * @param n_chains number of parallel chains
       * @param chain_size size of the chains
       * @param seed the seed for random number generation
       * @param dir_output output directory
       * @param chain_file output file
       * @param start starting position in the chains
       * @param stop final position in the chains
       * @param thin interval of parameter in output
       *
       * @return none
       */
       void sample_likelihood(double xmin, double xmax, const statistics::LikelihoodType likelihood_type, const statistics::LogLikelihood_function loglikelihood_function, const bool cov, const int n_chains, const int chain_size, const int seed, const string dir_output, const string chain_file, const double start=0.5, const double stop=1, const int thin=1);

      /**
       * @brief compute and write the model using the stored 
       * parameter values
       *
       * @param xx vector of point at which the model
       * is computed
       * @param dir_model the output directory of the model
       * @param file_model the name of the file
       *
       * @return none
       */
       virtual void write_model(const vector<double> xx, const string dir_model, const string file_model)
      { cosmobl::ErrorMsg("Error in write_model of Modelling.h!");}
	 

      /**
       * @brief compute and write the model using the stored 
       * parameter values
       *
       * @param xx vector of point at which the model
       * is computed
       * @param parameters vector of parameters values
       * at which the model is computed
       * @param dir_model the output directory of the model
       * @param file_model the name of the file
       *
       * @return none
       */
       virtual void write_model_parameters(const vector<double> xx, const vector<double> parameters, const string dir_model, const string file_model)
      { cosmobl::ErrorMsg("Error in write_model_parameters of Modelling.h!");}

      /**
       * @brief compute and write the model using the stored 
       * parameter values
       *
       * @param xx vector of point at which the model
       * is computed, first axis
       * @param yy vector of point at which the model
       * is computed, second axis
       * @param dir_model the output directory of the model
       * @param file_model the name of the file
       *
       * @return none
       */
       virtual void write_model(const vector<double> xx, const vector<double> yy, const string dir_model, const string file_model)
       {cosmobl::ErrorMsg("Error in write_model of Modelling.h!");}

      /**
       * @brief compute and write the model using the stored 
       * parameter values
       *
       * @param xx vector of point at which the model
       * is computed, first axis
       * @param yy vector of point at which the model
       * is computed, second axis
       * @param parameters vector of parameters values
       * at which the model is computed
       * @param dir_model the output directory of the model
       * @param file_model the name of the file
       *
       * @return none
       */
       virtual void write_model_parameters(const vector<double> xx, const vector<double> yy, const vector<double> parameters, const string dir_model, const string file_model)
       {cosmobl::ErrorMsg("Error in write_model_parameters of Modelling.h!");}
    };
  }
}

#endif
