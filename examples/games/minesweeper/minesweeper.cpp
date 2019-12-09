#include <xtd/xtd.forms>

using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms;

namespace minesweeper {
  enum class level {
    beginer,
    intermediate,
    expert,
    //custom,
  };

  enum class cell_state {
    unchecked,
    checked,
    flag,
    question,
    mine,
    exploded_mine,
    error,
  };

  class cell : public user_control {
  public:
    cell() {
      font(drawing::font(font().name(), 16));
      size({30, 30});
     };

    const point& cell_location() const {return cell_location_;}
    void cell_location(const point& value) {
      if (cell_location_ != value) {
        cell_location_ = value;
      }
    }

    bool has_mine() const {return has_mine_;}
    void has_mine(bool value) {
      if (has_mine_ != value) {
        has_mine_ = value;
      }
    }
 
    bool has_neighbors() const {return neighbors_;}

    int neighbors() const {return neighbors_;}
    void neighbors(int value) {
      if (neighbors_ != value) {
        neighbors_ = value;
        invalidate();
      }
    }

    cell_state state() const {return state_;}
    void state(cell_state value) {
      if (state_ != value) {
        state_ = value;
        invalidate();
      }
    }
    
    void clear() {
      state_ = cell_state::unchecked;
      has_mine_ = false;
      neighbors_ = 0;
      invalidate();
    }

  protected:
    void on_paint(paint_event_args& e) override {
      std::map<cell_state, delegate<void(paint_event_args&)>> draw_state {{cell_state::unchecked, {*this, &cell::do_draw_unchecked}}, {cell_state::checked, {*this, &cell::do_draw_checked}}, {cell_state::flag, {*this, &cell::do_draw_flag}}, {cell_state::question, {*this, &cell::do_draw_question}}, {cell_state::mine, {*this, &cell::do_draw_mine}}, {cell_state::exploded_mine, {*this, &cell::do_draw_exploded_mine}}, {cell_state::error, {*this, &cell::do_draw_error}}};
      draw_state[state_](e);
      user_control::on_paint(e);
    }
    
  private:
    void do_draw_unchecked(paint_event_args& e) {
      draw_border_unchecked(e);
    }
    
    void do_draw_checked(paint_event_args& e) {
      draw_border_checked(e);
      color text_color = system_colors::control_text();
      if (neighbors_ == 6) text_color = fore_color();
      if (neighbors_ == 5) text_color = color::dark_red;
      if (neighbors_ == 4) text_color = color::dark_blue;
      if (neighbors_ == 3) text_color = color::red;
      if (neighbors_ == 2) text_color = color::green;
      if (neighbors_ == 1) text_color = color::blue;
      if (neighbors_ != 0) {
        ustring text = std::to_string(neighbors_);
        int x = (e.clip_rectangle().width() - e.graphics().measure_string(text, font()).width()) / 2;
        int y = (e.clip_rectangle().height() - e.graphics().measure_string(text, font()).height()) / 2;
        e.graphics().draw_string(text, font(), solid_brush(color::lighter(color::lighter(text_color))), x - 1, y - 1);
        e.graphics().draw_string(text, font(), solid_brush(color::darker(color::darker(text_color))), x + 1, y + 1);
        e.graphics().draw_string(text, font(), solid_brush(text_color), x, y);
      }
    }
    
    void do_draw_flag(paint_event_args& e) {
      draw_border_unchecked(e);
      image flag = image::from_data(flag_16x16);
      int x = (e.clip_rectangle().width() - flag.width()) / 2;
      int y = (e.clip_rectangle().height() - flag.height()) / 2;
      e.graphics().draw_image(flag, x, y);
    }
    
    void do_draw_question(paint_event_args& e) {
      draw_border_unchecked(e);
      int x = (e.clip_rectangle().width() - e.graphics().measure_string("?", font()).width()) / 2;
      int y = (e.clip_rectangle().height() - e.graphics().measure_string("?", font()).height()) / 2;
      e.graphics().draw_string("?", font(), solid_brush(fore_color()), x, y);
    }
    
    void do_draw_mine(paint_event_args& e) {
      draw_border_checked(e);
      image mine = image::from_data(mine_16x16);
      int x = (e.clip_rectangle().width() - mine.width()) / 2;
      int y = (e.clip_rectangle().height() - mine.height()) / 2;
      e.graphics().draw_image(mine, x, y);
    }
    
    void do_draw_exploded_mine(paint_event_args& e) {
      e.graphics().clear(color::red);
      draw_border_checked(e);
      image mine = image::from_data(mine_16x16);
      int x = (e.clip_rectangle().width() - mine.width()) / 2;
      int y = (e.clip_rectangle().height() - mine.height()) / 2;
      e.graphics().draw_image(mine, x, y);
    }

    void do_draw_error(paint_event_args& e) {
      draw_border_checked(e);
      image mine = image::from_data(mine_16x16);
      int x = (e.clip_rectangle().width() - mine.width()) / 2;
      int y = (e.clip_rectangle().height() - mine.height()) / 2;
      e.graphics().draw_image(mine, x, y);
      e.graphics().draw_line(pen(color::red, 2), 0, 0, e.clip_rectangle().width(), e.clip_rectangle().height());
      e.graphics().draw_line(pen(color::red, 2), e.clip_rectangle().width(), 0, 0, e.clip_rectangle().height());
    }

    void draw_border_unchecked(paint_event_args& e) {
      e.graphics().draw_line(pen(color::lighter(color::lighter(color::lighter(back_color())))), 0, 0, e.clip_rectangle().width(), 0);
      e.graphics().draw_line(pen(color::lighter(color::lighter(back_color()))), 0, 1, e.clip_rectangle().width(), 1);
      e.graphics().draw_line(pen(color::lighter(back_color())), 1, 2, e.clip_rectangle().width(), 2);
      e.graphics().draw_line(pen(color::lighter(color::lighter(color::lighter(back_color())))), 0, 0, 0, e.clip_rectangle().height());
      e.graphics().draw_line(pen(color::lighter(color::lighter(back_color()))), 1, 1, 1, e.clip_rectangle().height());
      e.graphics().draw_line(pen(color::lighter(back_color())), 2, 2, 2, e.clip_rectangle().height());
      e.graphics().draw_line(pen(color::darker(back_color())), 2, e.clip_rectangle().height() - 3, e.clip_rectangle().width(), e.clip_rectangle().height() - 3);
      e.graphics().draw_line(pen(color::darker(color::darker(back_color()))), 1, e.clip_rectangle().height() - 2, e.clip_rectangle().width(), e.clip_rectangle().height() - 2);
      e.graphics().draw_line(pen(color::darker(color::darker(color::darker(back_color())))), 0, e.clip_rectangle().height() - 1, e.clip_rectangle().width(), e.clip_rectangle().height() - 1);
      e.graphics().draw_line(pen(color::darker(back_color())), e.clip_rectangle().width() - 3, 2, e.clip_rectangle().width() - 3, e.clip_rectangle().height() - 3);
      e.graphics().draw_line(pen(color::darker(color::darker(back_color()))), e.clip_rectangle().width() - 2, 1, e.clip_rectangle().width() - 2, e.clip_rectangle().height() - 2);
      e.graphics().draw_line(pen(color::darker(color::darker(color::darker(back_color())))), e.clip_rectangle().width() - 1, 0, e.clip_rectangle().width() - 1, e.clip_rectangle().height() - 1);
    }
    
    void draw_border_checked(paint_event_args& e) {
      e.graphics().draw_line(pen(color::darker(back_color())), 0, 0, e.clip_rectangle().width(), 0);
      e.graphics().draw_line(pen(color::darker(back_color())), 0, 0, 0, e.clip_rectangle().height());
      e.graphics().draw_line(pen(color::lighter(back_color())), 1, e.clip_rectangle().height() - 1, e.clip_rectangle().width(), e.clip_rectangle().height() - 1);
      e.graphics().draw_line(pen(color::lighter(back_color())), e.clip_rectangle().width() - 1, 1, e.clip_rectangle().width() - 1, e.clip_rectangle().height() - 1);
    }
    
    #include "resources/flag_16x16.xpm"
    #include "resources/mine_16x16.xpm"
    cell_state state_ = cell_state::unchecked;
    bool has_mine_ = false;
    int neighbors_ = 0;
    point cell_location_;
  };

  class form_main : public form {
    using column_cell = std::vector<std::shared_ptr<cell>>;
    using row_cell = std::vector<column_cell>;
    using grid_size = drawing::size;
  public:
    form_main() {
      text("Minesweeper");
      auto_size_mode(forms::auto_size_mode::grow_and_shrink);
      auto_size(true);
      back_color(color::silver);
      fore_color(color::black);
      
      status_panel.parent(*this);
      status_panel.height(60);
      game_panel.parent(*this);
      game_panel.location({0, 60});
      change_level(level::intermediate);
      status_panel.width(client_size().width());

      mine_count_label.parent(status_panel);
      mine_count_label.location({22, 22});
      mine_count_label.auto_size(true);
      mine_count_label.back_color(color::black);
      mine_count_label.fore_color(color::red);

      stopwatch_label.parent(status_panel);
      stopwatch_label.auto_size(true);
      stopwatch_label.back_color(color::black);
      stopwatch_label.fore_color(color::red);
      stopwatch_label.location({status_panel.width() - stopwatch_label.width() - 22, 22});

      start_game.parent(status_panel);
      start_game.image(bitmap(image::from_data(smiley1_32x32), {24, 24}));
      start_game.size({36, 36});
      start_game.location({status_panel.size().width() / 2 - 18, 17});
      start_game.click += [this]{
        new_game();
      };
      
      stopwatch.interval(1000);
      stopwatch.tick += [this] {
        if (stopwatch_count_ <= 999) stopwatch_label.text(strings::format("{:D3}", ++stopwatch_count_));
      };
    }
    
  private:
    void change_level(level level) {
      level_ = level;
      cells_.clear();
      grid_size_ = std::map<minesweeper::level, grid_size> {{minesweeper::level::beginer, {9, 9}}, {minesweeper::level::intermediate, {16, 16}}, {minesweeper::level::expert, {30, 16}}} [level_];
      mine_count_ = std::map<minesweeper::level, int> {{minesweeper::level::beginer, 10}, {minesweeper::level::intermediate, 40}, {minesweeper::level::expert, 99}} [level_];

      game_panel.size({30 + grid_size_.width() * cell().width(),30 + grid_size_.height() * cell().height()});

      cells_ = row_cell(grid_size_.width(), column_cell(grid_size_.height()));
      for (int y = 0; y < grid_size_.height(); y++) {
        for (int x = 0; x < grid_size_.width(); x++) {
          cells_[x][y] = std::make_shared<cell>();
          cells_[x][y]->parent(game_panel);
          cells_[x][y]->cell_location({x, y});
          cells_[x][y]->location({15 + x * cells_[x][y]->size().width(), 15 + y * cells_[x][y]->size().height()});
          cells_[x][y]->mouse_up += [this](control& sender, const mouse_event_args& e) {
            if (game_over_) return;
            minesweeper::cell& cell = static_cast<minesweeper::cell&>(sender);
            stopwatch.enabled(true);
            if (e.button() == mouse_buttons::left) {
              if (cell.state() == cell_state::question) cell.state(cell_state::unchecked);
              if (cell.state() == cell_state::unchecked) {
                if (!cell.has_mine()) {
                  check_neighbors(cell.cell_location());
                  cdebug << format("total cells = {}, mine to found = {}, mine uncheck = {}", grid_size_.width() * grid_size_.height(), mine_count_, grid_size_.width() * grid_size_.height() - checked_cell_count_) << std::endl;
                  if (grid_size_.width() * grid_size_.height() - checked_cell_count_ == mine_count_) {
                    stopwatch.enabled(false);
                    game_over_ = true;
                    start_game.image(bitmap(image::from_data(smiley3_16x16), {24, 24}));
                    for (int index1 = 0; index1 < grid_size_.height(); index1++)
                      for (int index2 = 0; index2 <grid_size_.width(); index2++)
                        if (cells_[index2][index1]->has_mine())
                          cells_[index2][index1]->state(cell_state::mine);
                    message_box::show(*this, "You win!");
                  }
                } else {
                  stopwatch.enabled(false);
                  game_over_ = true;
                  start_game.image(bitmap(image::from_data(smiley2_16x16), {24, 24}));
                  for (int index1 = 0; index1 < grid_size_.height(); index1++) {
                    for (int index2 = 0; index2 <grid_size_.width(); index2++) {
                      if (cells_[index2][index1]->state() == cell_state::flag && !cells_[index2][index1]->has_mine())
                        cells_[index2][index1]->state(cell_state::error);
                      if (cells_[index2][index1]->has_mine())
                        cells_[index2][index1]->state(cell_state::mine);
                    }
                  }
                  cell.state(cell_state::exploded_mine);
                  message_box::show(*this, "BOOOooomm!");
                }
              }
            } else if (e.button() == mouse_buttons::right) {
              if (cell.state() == cell_state::unchecked) {
                cell.state(cell_state::flag);
                ++flagged_mine_count_;
              } else if (cell.state() == cell_state::flag) {
                cell.state(cell_state::question);
                --flagged_mine_count_;
              } else if (cell.state() == cell_state::question) cell.state(cell_state::unchecked);
              if ((mine_count_ - flagged_mine_count_) >= 0 && (mine_count_ - flagged_mine_count_) <= 999) mine_count_label.text(strings::format("{:D3}", mine_count_ - flagged_mine_count_));
              else if (mine_count_ - flagged_mine_count_ >= -99) mine_count_label.text(strings::format("{:D2}", mine_count_ - flagged_mine_count_));
            }
          };
        }
      }
      new_game();
    }

    void new_game() {
      game_over_ = false;
      stopwatch.enabled(false);
      checked_cell_count_ = 0;
      flagged_mine_count_ = 0;
      stopwatch_count_ = 0;
      for (int y = 0; y < grid_size_.height(); y++)
        for (int x = 0; x < grid_size_.width(); x++)
          cells_[x][y]->clear();
      
      std::random_device rand;
      for (int count = 0; count < mine_count_; count++) {
        int x = std::uniform_int_distribution<int>{0, grid_size_.width() - 1}(rand);;
        int y = std::uniform_int_distribution<int>{0, grid_size_.height() - 1}(rand);;

        if (cells_[x][y]->has_mine()) {
          count--;
          continue;
        }
        cells_[x][y]->has_mine(true);
      }
      mine_count_label.text(strings::format("{:D3}", mine_count_ - flagged_mine_count_));
      stopwatch_label.text("000");
      start_game.image(bitmap(image::from_data(smiley1_32x32), {24, 24}));
    }
    
    void check_neighbors(const point& cell_location) {
      if (checked_cell(cell_location) != 0) return;
      for (int y = cell_location.y() - 1; y <= cell_location.y() + 1; y++) {
        for (int x = cell_location.x() - 1; x <= cell_location.x() + 1; x++) {
          if (y >= 0 && y < grid_size_.height() && x >= 0 && x < grid_size_.width() && cells_[x][y]->state() == cell_state::unchecked && checked_cell({x, y}) == 0) {
            check_neighbors({x, y});
          }
        }
      }
    }

    int checked_cell(const point& cell_location) {
      if (cells_[cell_location.x()][cell_location.y()]->state() == cell_state::unchecked) {
        cells_[cell_location.x()][cell_location.y()]->state(cell_state::checked);
        checked_cell_count_++;
      }

      for (int y = cell_location.y() - 1; y <= cell_location.y() + 1; y++) {
        for (int x = cell_location.x() - 1; x <= cell_location.x() + 1; x++) {
          if (y >= 0 && y < grid_size_.height() && x >= 0 && x < grid_size_.width() && cells_[x][y]->has_mine()) {
            cells_[cell_location.x()][cell_location.y()]->neighbors(cells_[cell_location.x()][cell_location.y()]->neighbors() + 1);
          }
        }
      }

      return cells_[cell_location.x()][cell_location.y()]->neighbors();
    }

    #include "resources/smiley1_32x32.xpm"
    #include "resources/smiley2_16x16.xpm"
    #include "resources/smiley3_16x16.xpm"
    panel status_panel;
    lcd_label mine_count_label;
    lcd_label stopwatch_label;
    button start_game;
    panel game_panel;
    timer stopwatch;
    grid_size grid_size_;
    int mine_count_;
    row_cell cells_;
    level level_ = level::beginer;
    bool game_over_ = false;
    int checked_cell_count_ = 0;
    int flagged_mine_count_ = 0;
    int stopwatch_count_ = 0;
  };
}

int main() {
  xtd::forms::application::run(minesweeper::form_main());
}