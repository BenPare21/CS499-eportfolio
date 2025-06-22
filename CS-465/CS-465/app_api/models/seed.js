Trip.create([
    {
      code: 'NEPAL2023',
      name: 'Himalayan Adventure',
      length: '14 days',
      start: new Date('2025-07-01'),
      resort: 'Everest Base Camp',
      perPerson: '2500',
      image: 'suite.jpg',
      description: 'Trek through the Himalayas!'
    },
    {
      code: 'FRANCE2023',
      name: 'Paris Getaway',
      length: '5 days',
      start: new Date('2025-05-15'),
      resort: 'Champs-Élysées',
      perPerson: '1800',
      image: 'rooms.png', // changed from paris.jpg
      description: 'Romantic retreat in the city of lights.'
    }
  ], (err) => {
    if (err) {
      console.log('Seed error:', err);
    } else {
      console.log('Database seeded successfully');
    }
    mongoose.connection.close(); // important
  });
  