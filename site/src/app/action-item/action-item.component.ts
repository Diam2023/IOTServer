import { Component, Input } from '@angular/core';
import { Action } from '../model/action';

@Component({
  selector: 'app-action-item',
  standalone: true,
  imports: [],
  template: `
  <button (click)="sendAction">{{ actionItem.action_name }}</button>
  `,
  styleUrl: './action-item.component.css'
})

export class ActionItemComponent {
  @Input() actionItem!: Action;

  sendAction() {
    // this.router.navigate(['/']);

  }
}
