#ifndef __OBSERVER__H
#define __OBSERVER__H

class Subject;

class Observer {
 public:
  virtual void notify(Subject &whoNotified) = 0;
  virtual ~Observer() = default;
};

#endif
