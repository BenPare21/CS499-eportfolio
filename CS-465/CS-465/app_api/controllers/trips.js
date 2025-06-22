const mongoose = require('mongoose');
const Trip = require('../models/travlr');
const Model = mongoose.model('trips');

//Get: trips - lists all the trips
//Regardless of outcome, refonse must include HTML status code
//and JSON message to the requesting cleint
const tripList = async (req, res) =>  {
    const q = await Model
        .find({}) // No filter, return all records
        .exec();

        //Uncomment the following line to show results of the querey
        //On the console
        //console.log(q);

    if(!q)
    { // Database returned no data
        return res
            .status(404)
            .json(err);
    } 
    else // return resulting trip list
    {
        return res
            .status(200)
            .json(q)
    }

};

const tripsFindbyCode = async(req, res) => {
    const q = await Model
        .find({'code': req.param.tripCode}) // returns single record
        .exec 
        //uncomment to show querey
        //console.log(q);
    if(!q)
    { //database returned no data
        return res
            .status(404)
            .json(err);

    }
    else
    {// return resulting trip list
        return res 
            .status(200)
            .json(q)
    }
}





module.exports = {
    tripList
};