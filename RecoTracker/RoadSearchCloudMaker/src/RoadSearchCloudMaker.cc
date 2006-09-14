//
// Package:         RecoTracker/RoadSearchCloudMaker
// Class:           RoadSearchCloudMaker
// 
// Description:     Calls RoadSeachCloudMakerAlgorithm
//                  to find RoadSearchClouds.
//
// Original Author: Oliver Gutsche, gutsche@fnal.gov
// Created:         Sat Jan 14 22:00:00 UTC 2006
//
// $Author: llista $
// $Date: 2006/08/01 14:19:04 $
// $Revision: 1.10 $
//

#include <memory>
#include <string>

#include "RecoTracker/RoadSearchCloudMaker/interface/RoadSearchCloudMaker.h"

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/RoadSearchCloud/interface/RoadSearchCloudCollection.h"

#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

namespace cms
{

  RoadSearchCloudMaker::RoadSearchCloudMaker(edm::ParameterSet const& conf) : 
    roadSearchCloudMakerAlgorithm_(conf) ,
    conf_(conf)
  {
    produces<RoadSearchCloudCollection>();
  }


  // Virtual destructor needed.
  RoadSearchCloudMaker::~RoadSearchCloudMaker() { }  

  // Functions that gets called by framework every event
  void RoadSearchCloudMaker::produce(edm::Event& e, const edm::EventSetup& es)
  {
    // retrieve producer name of input SeedCollection
    std::string seedProducer = conf_.getParameter<std::string>("SeedProducer");

    // Step A: Get Inputs 
    edm::Handle<TrajectorySeedCollection> seeds;
    e.getByLabel(seedProducer, seeds);

    // retrieve producer name of input SiStripRecHit2DCollection
    edm::InputTag rphirecHitsTag = conf_.getParameter<edm::InputTag>("rphirecHits");
    edm::InputTag stereorecHitsTag = conf_.getParameter<edm::InputTag>("stereorecHits");
    edm::InputTag recHitCollection = conf_.getParameter<edm::InputTag>("recHitCollection");

    edm::InputTag matchedrecHitsTag = conf_.getParameter<edm::InputTag>("matchedrecHits");

    // get Inputs 
    edm::Handle<SiStripRecHit2DCollection> rphirecHits;
    e.getByLabel( rphirecHitsTag, rphirecHits);
    edm::Handle<SiStripRecHit2DCollection> stereorecHits;
    e.getByLabel( stereorecHitsTag, stereorecHits);

    edm::Handle<SiStripMatchedRecHit2DCollection> matchedrecHits;
    e.getByLabel( matchedrecHitsTag, matchedrecHits);

    edm::Handle<SiPixelRecHitCollection> pixRecHits; // TMoulik
    e.getByLabel( recHitCollection, pixRecHits ); // TMoulik

    // Step B: create empty output collection
    std::auto_ptr<RoadSearchCloudCollection> output(new RoadSearchCloudCollection);

    // Step C: Invoke the seed finding algorithm
    roadSearchCloudMakerAlgorithm_.run(seeds,rphirecHits.product(),
				       stereorecHits.product(),matchedrecHits.product(),pixRecHits.product(),
				       es,*output);

    // Step D: write output to file
    e.put(output);

  }

}
