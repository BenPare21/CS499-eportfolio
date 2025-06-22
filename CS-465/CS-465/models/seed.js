const mongoose = require('mongoose');
const Trip = require('./travlr'); // Correct model import

mongoose.connect('mongodb://localhost:27017/travlr', { useNewUrlParser: true, useUnifiedTopology: true });

const trips = [
    { 
        name: 'Sweet Delights Tour', 
        destination: 'Dessert Haven', 
        duration: 3, 
        price: 1200, 
        description: 'Satisfy your sweet tooth with a tour of the world’s finest desserts!', 
        image: 'desserts.jpg' 
    },
    { 
        name: 'Underwater Adventure', 
        destination: 'Ocean Dive Resort', 
        duration: 7, 
        price: 1800, 
        description: 'Dive into crystal clear waters and discover marine life!', 
        image: 'dive-site.png' 
    },
    { 
        name: 'Luxury First Class Retreat', 
        destination: 'Elite Class Resort', 
        duration: 3, 
        price: 2500, 
        description: 'Experience the ultimate in luxury and relaxation!', 
        image: 'first-class.jpg' 
    }
];


Trip.insertMany(trips)
    .then(() => {
        console.log('Database populated with seed data!');
        mongoose.connection.close();
    })
    .catch((err) => console.error(err));
