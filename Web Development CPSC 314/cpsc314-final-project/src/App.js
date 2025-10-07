// Client ID 3a88d0bedcdf4a6f8180f2c67bcc1049
// Client Secret 5e97a934d89046fc9e1ceccecaa1fb8e 
// playlist-read-private
// https://accounts.spotify.com/authorize?client_id=3a88d0bedcdf4a6f8180f2c67bcc1049&response_type=code&redirect_uri=http://localhost:3000/
// code AQAHQb6005bnnpB1E_Wp5NhNK89FQkY0tzCJ0JbCun0G2C9s_SIG7BWkKurll_gmzd6viaGluN3Ux6nyy-bXpyCqOtsTCdCw1kNpT0vdAmUfEsbSC1Mk_-MvVajtiMetSu3g_0WReLPB1bmm7Knx4dR4cbG3K_bnF3MRzHoKJDb8w_mWsJU7FCXeg6Vk403FFZuhQE5ZmEuYdEOiiYzLaosLmw

// 3a88d0bedcdf4a6f8180f2c67bcc1049:5e97a934d89046fc9e1ceccecaa1fb8e 
// M2E4OGQwYmVkY2RmNGE2ZjgxODBmMmM2N2JjYzEwNDk6NWU5N2E5MzRkODkwNDZmYzllMWNlY2NlY2FhMWZiOGU=

// curl -H "Authorization: Basic M2E4OGQwYmVkY2RmNGE2ZjgxODBmMmM2N2JjYzEwNDk6NWU5N2E5MzRkODkwNDZmYzllMWNlY2NlY2FhMWZiOGU=" -d grant_type=authorization_code -d code=AQAHQb6005bnnpB1E_Wp5NhNK89FQkY0tzCJ0JbCun0G2C9s_SIG7BWkKurll_gmzd6viaGluN3Ux6nyy-bXpyCqOtsTCdCw1kNpT0vdAmUfEsbSC1Mk_-MvVajtiMetSu3g_0WReLPB1bmm7Knx4dR4cbG3K_bnF3MRzHoKJDb8w_mWsJU7FCXeg6Vk403FFZuhQE5ZmEuYdEOiiYzLaosLmw -d redirect_uri=http%3A%2F%2Flocalhost%3A3000%2F https://accounts.spotify.com/api/token

// {
//   "access_token":"BQB45XZuwdCbNRg0U0vjRS3MWWqTtWBE-s7hqHxZFcC3LvOZBLa6sJAz5uuKrKkjhfKu4lCGGGGQnh4bg1h-FiBEiOrNzUCf5V5nG0mCdjYfXxnznxLKfVw-FK8CbeKTMv-hUruXpHlXGHxgYFWVlgxQprg",
//   "token_type":"Bearer",
//   "expires_in":3600,
//   "refresh_token":"AQAJ9wIhju47q3fHQyub3ewJW8QWgxc7erIRFDwFjd4-GJzatodd99SqfPTFBCPGGLrA87JFM9bk9IRPruOgulbQvFMDS9gbiEF75PBleEsJAUrShSscxzbZGlwAXwOTWSw",
//   "scope":"playlist-read-private"
// }


import React from 'react';
import './App.css';

function App() {
  return (
    <div className="App">
      <div className='auth'>
        <h1>Sign Into Spotify</h1>
        <div className='button center p-top'>
            <a href='https://accounts.spotify.com/authorize?client_id=3a88d0bedcdf4a6f8180f2c67bcc1049&response_type=code&redirect_uri=http%3A%2F%2Flocalhost%3A3000%2F&scope=playlist-read-private'>
              Authorize
            </a>
          </div>
      </div>
    </div>
  );
}

{/* <form>
<div className='formheader'>
  <h1>Sign into Spotify</h1>
</div>
<div className='textbox'>
  <i className='far fa-user'></i>
  <input name='name' type='text' placeholder='Username'/>
</div>
<div className='textbox'>
  <i className='fas fa-unlock'></i>
  <input name='email' type='password' placeholder='Password'/>
</div>
</form> */}

export default App;
