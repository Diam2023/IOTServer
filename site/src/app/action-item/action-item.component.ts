import { Component, inject, Input, Output } from '@angular/core';
import { Action } from '../model/action';
import { ActionService } from '../service/action.service';
import { MessageService } from 'primeng/api';

@Component({
  selector: 'app-action-item',
  standalone: true,
  imports: [],
  template: `
  <button (click)="sendAction()">{{ actionItem.action_name }}</button>
  `,
  styleUrl: './action-item.component.css'
})

export class ActionItemComponent {
  @Input() actionItem!: Action;


  constructor(private actionService: ActionService, private messageService: MessageService) {
  }

  sendAction() {
    console.log("send Action");
    this.actionService.callAction(this.actionItem.action_name).then(r => {
      if (r) {
        this.messageService.add({ severity: 'info', summary: "Action", detail: "发送成功", });
      } else {
        this.messageService.add({ severity: 'info', summary: "Action", detail: "发送失败", });
      }
    }).catch(e => {
      alert(e)
    });
  }
}
