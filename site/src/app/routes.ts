import { Routes } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { DetailsComponent } from './details/details.component';

const routeConfig: Routes = [
    {
      path: '',
      component: HomeComponent,
      title: 'Home page'
    },
    {
      path: 'details/:sn',
      component: DetailsComponent,
      title: 'DeviceDetail',
    },
    {
      path: 'login',
      component: LoginComponent,
      title: 'Login'
    }
  ];
  
  export default routeConfig;