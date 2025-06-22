const mongoose = require('mongoose');

const tripSchema = new mongoose.Schema({
    name: { 
        type: String, 
        required: true, 
        minlength: [3, 'Name must be at least 3 characters long'], 
        maxlength: [100, 'Name must be at most 100 characters long']
    },
    destination: { 
        type: String, 
        required: true 
    },
    duration: { 
        type: Number, 
        required: true, 
        min: [1, 'Duration must be at least 1 day']
    },
    price: { 
        type: Number, 
        required: true, 
        min: [0, 'Price must be a positive number']
    },

    description: { 
        type: String, 
        maxlength: [500, 'Description must be at most 500 characters long'],
        required: false  // Make this field optional
    },
    

    image: { 
        type: String, 
        validate: {
            validator: function(v) {
                return /^(https?:\/\/)?[\w-]+(\.[\w-]+)+[/#?]?.*$/.test(v); // Simple URL pattern
            },
            message: 'Invalid image URL'
        },
        required: false  // Optional field
    }
    });

module.exports = mongoose.model('Trip', tripSchema);
