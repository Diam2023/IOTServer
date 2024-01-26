import { Component, Input } from '@angular/core';
import { Action } from '../model/action';
import { ActionService } from '../service/action.service';

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


  constructor(private actionService: ActionService) {
  }

  sendAction() {



    // this.router.navigate(['/']);
  }
}
