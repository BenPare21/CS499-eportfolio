const express = require('express'); //Express app
const router = express.Router(); // Router logic

//This is where we import the controllers we will route
const tripsController = reqire('../controllers.trips');

// define route for out trips endpoint
router
    .router('trips')
    .get(tripsController.tripsList); //GET Method routes tripList

module.exports = router;