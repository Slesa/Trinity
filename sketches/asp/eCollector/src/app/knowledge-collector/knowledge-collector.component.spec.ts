import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { KnowledgeCollectorComponent } from './knowledge-collector.component';

describe('KnowledgeCollectorComponent', () => {
  let component: KnowledgeCollectorComponent;
  let fixture: ComponentFixture<KnowledgeCollectorComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ KnowledgeCollectorComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(KnowledgeCollectorComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
