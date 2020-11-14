
const express = require('express')
const fetch = require('node-fetch');
const app = express()
const port = 3000

app.use(express.urlencoded());

app.get('/', (req, res) => {
  res.sendFile(`${__dirname}/index.html`);
})

app.post('/buzz', (req, res) => {
  if (req.body.color && req.body.color === 'blue') {
  fetch('http://192.168.1.125/');
  }
  res.send("okay");

})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
