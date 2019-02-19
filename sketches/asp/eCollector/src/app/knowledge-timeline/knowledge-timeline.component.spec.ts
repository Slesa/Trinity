import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { KnowledgeTimelineComponent } from './knowledge-timeline.component';

describe('KnowledgeTimelineComponent', () => {
  let component: KnowledgeTimelineComponent;
  let fixture: ComponentFixture<KnowledgeTimelineComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ KnowledgeTimelineComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(KnowledgeTimelineComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
