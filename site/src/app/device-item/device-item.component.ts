import { Component, Input } from '@angular/core';
import { Device } from '../model/device';
import { Router, RouterLink } from '@angular/router';

@Component({
  selector: 'app-device-item',
  standalone: true,
  imports: [RouterLink],
  template: `
  <section class="listing">
    <a [routerLink]="['details', deviceItem.device_sn]">
      <h2 class="listing-heading">{{ deviceItem.device_name }}</h2>
      <p class="listing-sn">SN: {{ deviceItem.device_sn }}</p>
      <p class="listing-permission">Premission: {{ deviceItem.target_permission_level }}</p>
    </a>
  </section>
  `,
  styleUrl: './device-item.component.css'
})

export class DeviceItemComponent {
  @Input() deviceItem!: Device;

  constructor(private router: Router) {

  }
}
