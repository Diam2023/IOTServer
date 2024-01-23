import { Component } from '@angular/core';
import { HomeComponent } from './home/home.component';
import { ActivatedRoute, Router, RouterLink, RouterModule } from '@angular/router';
import { DataStorge } from './utils/DataStorge';
import routeConfig from './routes';
import { AppCache } from './utils/AppCache';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    HomeComponent,
    RouterModule
  ],
  template: `
  <main>
    <a [routerLink]="['/']">
      <header class="brand-name">
        <img class="brand-logo" src="/assets/logo.svg" alt="logo" aria-hidden="true">
      </header>
    </a>
    <section class="content">
      <router-outlet></router-outlet>
    </section>
  </main>`,
  styleUrls: ['./app.component.css'],
})


export class AppComponent {
  title = 'homes';
  constructor(private appCache: AppCache, private route: Router) {

    if (appCache.isLoggedIn())
    {
      this.route.navigate(['/login']);
    }
  }

}
