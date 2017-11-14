#pragma once

/* Copyright 2017 CNRS-UM LIRMM, CNRS-AIST JRL
 *
 * This file is part of TVM.
 *
 * TVM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TVM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with TVM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <tvm/Clock.h>
#include <tvm/Task.h>
#include <tvm/requirements/SolvingRequirements.h>
#include <tvm/task_dynamics/abstract/TaskDynamics.h>

#include <memory>
#include <vector>

namespace tvm
{

  class TVM_DLLAPI TaskWithRequirements
  {
  public:
    TaskWithRequirements(const Task& task, requirements::SolvingRequirements req);

    Task task;
    requirements::SolvingRequirements requirements;
  };

  typedef std::shared_ptr<TaskWithRequirements> TaskWithRequirementsPtr;

  class TVM_DLLAPI ControlProblem
  {
  public:
    TaskWithRequirementsPtr add(const Task& task, const requirements::SolvingRequirements& req = {});
    TaskWithRequirementsPtr add(ProtoTask proto, TaskDynamicsPtr td, const requirements::SolvingRequirements& req = {});
    void add(TaskWithRequirementsPtr tr);
    void remove(TaskWithRequirements* tr);
    const std::vector<TaskWithRequirementsPtr>& tasks() const;

  private:
    //Note: we want to keep the tasks in the order they were introduced, mostly
    //for human understanding and debugging purposes, so that we take a
    //std::vector.
    //If this induce too much overhead when adding/removing a constraint, then
    //we should consider std::set.
    std::vector<TaskWithRequirementsPtr> tr_;
  };
}  // namespace tvm