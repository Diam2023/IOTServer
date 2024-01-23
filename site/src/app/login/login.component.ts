import { Component } from '@angular/core';
import { DataStorge } from '../utils/DataStorge';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [],
  template: `
    <p>
      login works!
    </p>
  `,
  styleUrl: './login.component.css'
})

export class LoginComponent {

  constructor(private dataStorage: DataStorge)
  {
  }
}
